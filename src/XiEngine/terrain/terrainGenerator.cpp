#include "terrainGenerator.h"

#include "../terrain/quadTreeFace.h"
#include "../terrain/quadTreeNode.h"
#include "../terrain/quadTreePatch.h"
#include "../terrain/terrain.h"

TerrainGenerator::TerrainGenerator(Terrain* terrain) :
	terrain_(terrain),
	sleeping_(true),
	shouldExit_(false)
{
	thread_ = std::thread(&TerrainGenerator::mainLoop, this);
}

TerrainGenerator::~TerrainGenerator()
{
	shouldExit_.store(true);
	wakeUpThread();
	thread_.join();
}

void TerrainGenerator::pushQueue(QuadTreePatch* patch)
{
	{
		std::lock_guard<std::mutex> lck(queueMutex_);
		queue_.push(std::make_pair(patch->getID(), patch));
	}

	wakeUpThread();
}

void TerrainGenerator::dismiss(unsigned int ID)
{
	std::lock_guard<std::mutex> lck(toDismissMutex_);
	toDismiss_.insert(ID);
}

unsigned int TerrainGenerator::queueSize()
{
	std::lock_guard<std::mutex> lck(queueMutex_);
	unsigned int size = queue_.size();
	
	return size;
}

void TerrainGenerator::mainLoop()
{
	while (!shouldExit_.load())
	{
		if (queueSize() == 0)
		{
			std::unique_lock<std::mutex> lk(cvMutex_);
			sleeping_ = true;
			cv_.wait(lk, [this] {return !sleeping_;});
		}
		else
		{
			QuadTreePatch* patch = nullptr;

			{
				std::lock_guard<std::mutex> lck(queueMutex_);
				std::pair<unsigned int, QuadTreePatch*> pair = queue_.front();
				queue_.pop();

				if (!isDismissed(pair.first))
					patch = pair.second;

			}

			if(patch != nullptr)
				generate(patch);
		}
	}
}

void TerrainGenerator::wakeUpThread()
{
	std::unique_lock<std::mutex> lck(cvMutex_);
	sleeping_ = false;
	cv_.notify_one();
}

void TerrainGenerator::generate(QuadTreePatch* patch)
{
	if (patch->status_.load() != UNLOADED)
		return;

	patch->status_.store(LOADING);

	unsigned int parentOffsetX = patch->node_->lieOnEast() ? (patch->edgeSize_ >> 1) : 0;
	unsigned int parentOffsetY = !patch->node_->lieOnNorth() ? (patch->edgeSize_ >> 1) : 0;

	for (unsigned int x = 0; x <= patch->edgeSize_; x++)
	{
		for (unsigned int y = 0; y <= patch->edgeSize_; y++)
		{
			Vector3 point;
			if (patch->parentPatch_ && (x & 1) == 0 && (y & 1) == 0)
			{
				point = patch->parentPatch_->positions_[patch->ind(parentOffsetX + (x >> 1), parentOffsetY + (y >> 1))];
			}
			else
			{
				Vector2 localPos = Vector2((float)x, (float)y) / (float)patch->edgeSize_;
				localPos -= 0.5f;
				localPos *= 2.0f;

				Vector2 facePos = patch->node_->localToFacePos(localPos);

				point = patch->node_->getFace()->getWorldPosition(facePos);
				if (shouldExit_.load())
					return;
				point = terrain_->projectOnSurface(point);
			}

			patch->positions_[patch->ind(x, y)] = point;
			patch->boundingBox_.merge(point);
		}
	}

	for (unsigned int x = 0; x <= patch->edgeSize_; x++)
	{
		for (unsigned int y = 0; y <= patch->edgeSize_; y++)
		{
			Vector2 localPos = Vector2((float)x, (float)y) / (float)patch->edgeSize_;
			localPos -= 0.5f;
			localPos *= 2.0f;
			Vector2 facePos = patch->node_->localToFacePos(localPos);

			Vector3 normal;
			//if (facePos.x_ > 0.99f || facePos.x_ < -0.99f || facePos.y_ > 0.99f || facePos.y_ < -0.99f)
			//	normal = Vector3(0.0f, 1.0f, 0.0f);
			//else
			{
				if (shouldExit_.load())
					return;
				Vector3 v1 = terrain_->projectOnSurface(patch->node_->getFace()->getWorldPosition(facePos + Vector2(0.1f, 0.1f)));
				if (shouldExit_.load())
					return;
				Vector3 v2 = terrain_->projectOnSurface(patch->node_->getFace()->getWorldPosition(facePos + Vector2(-0.1f, 0.1f)));
				if (shouldExit_.load())
					return;
				Vector3 v3 = terrain_->projectOnSurface(patch->node_->getFace()->getWorldPosition(facePos + Vector2(0.1f, -0.1f)));

				Plane plane(v1, v2, v3);
				normal = -plane.normal_.normalize();
			}
			patch->normals_[patch->ind(x, y)] = normal;
		}
	}

	patch->status_.store(RAM_LOADED);
}

bool TerrainGenerator::isDismissed(unsigned int ID)
{
	std::lock_guard<std::mutex> lck(toDismissMutex_);
	
	auto res = toDismiss_.find(ID);
	if (res != toDismiss_.end())
	{
		toDismiss_.erase(res);
		return true;
	}

	return false;
}
