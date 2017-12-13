#include "vector4.h"

#include "../precompiled.h"

#include "../math/vector3.h"

Vector4::Vector4()
{
	data[0] = 0.0f;
	data[1] = 0.0f;
	data[2] = 0.0f;
	data[3] = 0.0f;
}

Vector4::Vector4(float value)
{
	data[0] = value;
	data[1] = value;
	data[2] = value;
	data[3] = value;
}

Vector4::Vector4(float x, float y, float z, float w)
{
	data[0] = x;
	data[1] = y;
	data[2] = z;
	data[3] = w;
}

Vector4::Vector4(const Vector3& v, float w)
{
	data[0] = v.data[0];
	data[1] = v.data[1];
	data[2] = v.data[2];
	data[3] = w;
}

void Vector4::set(float x, float y, float z, float w)
{
	data[0] = x;
	data[1] = y;
	data[2] = z;
	data[3] = w;
}
	
Vector3 Vector4::xyz() const
{
	return Vector3(data[0], data[1], data[2]);
}
	
Vector4& Vector4::operator+=(const Vector4& v)
{
	data[0] += v.data[0];
	data[1] += v.data[1];
	data[2] += v.data[2];
	data[3] += v.data[3];
	return *this;
}
	
Vector4& Vector4::operator-=(const Vector4& v)
{
	data[0] -= v.data[0];
	data[1] -= v.data[1];
	data[2] -= v.data[2];
	data[3] -= v.data[3];
	return *this;
}
	
Vector4& Vector4::operator*=(const float& scalar)
{
	data[0] *= scalar;
	data[1] *= scalar;
	data[2] *= scalar;
	data[3] *= scalar;
	return *this;
}
	
Vector4& Vector4::operator/=(const float& scalar)
{
	data[0] /= scalar;
	data[1] /= scalar;
	data[2] /= scalar;
	data[3] /= scalar;
	return *this;
}
	
Vector4 Vector4::operator+(const Vector4& v) const
{
	return Vector4(data[0] + v.data[0], data[1] + v.data[1], data[2] + v.data[2], data[3] + v.data[3]);
}
	
Vector4 Vector4::operator-(const Vector4& v) const
{
	return Vector4(data[0] - v.data[0], data[1] - v.data[1], data[2] - v.data[2], data[3] - v.data[3]);
}
	
Vector4 Vector4::operator*(const float& scalar) const
{
	return Vector4(data[0] * scalar, data[1] * scalar, data[2] * scalar, data[3] * scalar);
}
	
Vector4 Vector4::operator/(const float& scalar) const
{
	return Vector4(data[0] / scalar, data[1] / scalar, data[2] / scalar, data[3] / scalar);
}
	
Vector4 Vector4::operator-() const
{
	return Vector4(-data[0], -data[1], -data[2], -data[3]);
}
	
float Vector4::length() const
{
	return sqrtf(data[0] * data[0] + data[1] * data[1] + data[2] * data[2] + data[3] * data[3]);
}
	
float Vector4::lengthSquared() const
{
	return data[0] * data[0] + data[1] * data[1] + data[2] * data[2] + data[3] * data[3];
}

Vector4& Vector4::normalize()
{
	float len = length();
	if (len != 0.0f)
		return (*this) /= len;
	return *this;
}
	
Vector4 Vector4::normalized() const
{
	Vector4 tempVector(*this);
	return tempVector.normalize();
}
	
float Vector4::dotProduct(const Vector4& v) const
{
	return data[0] * v.data[0] + data[1] * v.data[1] + data[2] * v.data[2] + data[3] * v.data[3];
}