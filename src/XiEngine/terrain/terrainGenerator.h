#pragma once

#include "../precompiled.h"

class QuadTreePatch;
class Terrain;

class TerrainGenerator
{
public:
	TerrainGenerator(Terrain* terrain);
	~TerrainGenerator();

	void pushQueue(QuadTreePatch* patch);
	void dismiss(unsigned int ID);

	unsigned int queueSize();

private:
	Terrain* terrain_;

	std::mutex toDismissMutex_;
	std::set<unsigned int> toDismiss_;

	std::mutex queueMutex_;
	std::queue<std::pair<unsigned int, QuadTreePatch*> > queue_;

	std::atomic_bool shouldExit_;
	std::thread thread_;

	bool sleeping_;
	std::mutex cvMutex_;
	std::condition_variable cv_;

	void mainLoop();
	void wakeUpThread();

	void generate(QuadTreePatch* patch);

	bool isDismissed(unsigned int ID);

	friend class Terrain;
};