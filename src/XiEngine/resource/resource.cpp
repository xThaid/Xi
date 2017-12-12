#include "resource.h"

Resource::Resource(const std::string& name) :
	memoryUse_(0),
	name_(name),
	nameHash_(name),
	status_(UNLOADED)
{
}

Resource::~Resource()
{
	if (status_ == READY_TO_USE)
		unload();
}

bool Resource::load()
{
	if (status_ == READY_TO_USE)
		return true;

	bool success = beginLoad();
	if (success)
		success &= endLoad();

	if (success)
		status_ = READY_TO_USE;
	else
		status_ = LOADING_FAILED;

	return success;
}

void Resource::unload()
{
	release();
	status_ = UNLOADED;
}

void Resource::setName(const std::string& name)
{
	name_ = name;
	nameHash_ = name;
}

void Resource::setMemoryUse(unsigned int size)
{
	memoryUse_ = size;
}

StringHash Resource::getType() const
{
	return StringHash(getTypeName());
}
