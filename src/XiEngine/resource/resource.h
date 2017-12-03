#pragma once

#include "../utils/stringHash.h"

#define XI_RESOURCE(typeName) \
    public: \
        using className = typeName; \
        static StringHash getTypeStatic() { return StringHash(#typeName); } \
        static const std::string getTypeNameStatic() { return #typeName; }

class Resource
{
	XI_RESOURCE(Resource)

public:
	Resource(const std::string& name);
	virtual ~Resource();

	bool load();

	virtual bool beginLoad() = 0;
	virtual bool endLoad() = 0;

	virtual void release() = 0;

	void setName(const std::string& name);
	void setMemoryUse(unsigned int size);
	
	inline std::string& getName() { return name_; }
	inline StringHash getNameHash() { return nameHash_; }
	inline unsigned int getMemoryUse() { return memoryUse_; }

	StringHash getType() const;
	virtual const std::string getTypeName() const = 0;

private:
	std::string name_;
	StringHash nameHash_;

	unsigned int memoryUse_;
};