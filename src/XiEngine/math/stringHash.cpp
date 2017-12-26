#include "stringHash.h"

StringHash::StringHash() :
	value(0)
{
}

StringHash::StringHash(unsigned int value) :
	value(value)
{
}

StringHash::StringHash(const char* str) :
	value(calculate(std::string(str)))
{
}

StringHash::StringHash(const std::string& str) :
	value(calculate(str))
{
}

StringHash& StringHash::operator=(const StringHash& strHash)
{
	value = strHash.value;
	return *this;
}

StringHash StringHash::operator+(const StringHash& strHash) const
{
	return StringHash(value + strHash.value);
}

StringHash& StringHash::operator+=(const StringHash& strHash)
{
	value += strHash.value;
	return *this;
}

unsigned int StringHash::calculate(const std::string& str)
{
	std::hash<std::string> hash;
	return hash(str);
}