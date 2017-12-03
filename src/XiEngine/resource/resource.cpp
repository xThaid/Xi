#include "resource.h"

Resource::Resource(const std::string& name) :
	memoryUse_(0),
	name_(name),
	nameHash_(name)
{
}

Resource::~Resource()
{
}

bool Resource::load()
{
	bool success = beginLoad();
	if (success)
		success &= endLoad();

	return success;
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
