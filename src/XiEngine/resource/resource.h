#pragma once

#include "../math/ximath.h"

#define XI_RESOURCE(typeName) \
    public: \
        using className = typeName; \
        static StringHash getTypeStatic() { return StringHash(#typeName); } \
        static const std::string getTypeNameStatic() { return #typeName; }


enum ResourceStatus
{
	UNLOADED,
	LOADING_FAILED,
	READY_TO_USE
};

class Resource
{
	XI_RESOURCE(Resource)

public:
	Resource(const std::string& name);
	virtual ~Resource();

	bool load();
	void unload();

	inline std::string& getName() { return name_; }
	inline StringHash getNameHash() { return nameHash_; }
	inline unsigned int getMemoryUse() { return memoryUse_; }
	inline ResourceStatus getStatus() { return status_; }

	StringHash getType() const;

protected:
	void setName(const std::string& name);
	void setMemoryUse(unsigned int size);

private:
	std::string name_;
	StringHash nameHash_;

	unsigned int memoryUse_;

	ResourceStatus status_;
	
	virtual bool beginLoad() = 0;
	virtual bool endLoad() = 0;

	virtual void release() = 0;

	virtual const std::string getTypeName() const = 0;
};
