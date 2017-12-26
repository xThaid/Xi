#pragma once

#include "../precompiled.h"

class StringHash
{
public:
	StringHash();
	StringHash(unsigned int value);
	StringHash(const char* str);
	StringHash(const std::string& str);

	StringHash& operator=(const StringHash& strHash);

	StringHash operator+(const StringHash& strHash) const;
	StringHash& operator+=(const StringHash& strHash);

	inline bool operator==(const StringHash& strHash) const { return value == strHash.value; }
	inline bool operator!=(const StringHash& strHash) const { return value != strHash.value; }
	inline bool operator>(const StringHash& strHash) const { return value > strHash.value; }
	inline bool operator<(const StringHash& strHash) const { return value < strHash.value; }

	inline unsigned int getValue() { return value; }

	static unsigned int calculate(const std::string& str);

private:
	unsigned int value;
};