#include "vector2.h"

#include "../precompiled.h"

Vector2::Vector2()
{
	data[0] = 0.0f;
	data[1] = 0.0f;
}

Vector2::Vector2(float value)
{
	data[0] = value;
	data[1] = value;
}

Vector2::Vector2(float x, float y)
{
	data[0] = x;
	data[1] = y;
}

void Vector2::set(float x, float y)
{
	data[0] = x;
	data[1] = y;
}

Vector2& Vector2::operator+=(const Vector2& v)
{
	data[0] += v.data[0];
	data[1] += v.data[1];
	return *this;
}

Vector2& Vector2::operator-=(const Vector2& v)
{
	data[0] -= v.data[0];
	data[1] -= v.data[1];
	return *this;
}

Vector2& Vector2::operator*=(const float& scalar)
{
	data[0] *= scalar;
	data[1] *= scalar;
	return *this;
}

Vector2& Vector2::operator/=(const float& scalar)
{
	data[0] /= scalar;
	data[1] /= scalar;
	return *this;
}
	
Vector2 Vector2::operator+(const Vector2& v) const
{
	return Vector2(data[0] + v.data[0], data[1] + v.data[1]);
}

Vector2 Vector2::operator-(const Vector2& v) const
{
	return Vector2(data[0] - v.data[0], data[1] - v.data[1]);
}

Vector2 Vector2::operator*(const float& scalar) const
{
	return Vector2(data[0] * scalar, data[1] * scalar);
}

Vector2 Vector2::operator/(const float& scalar) const
{
	return Vector2(data[0] / scalar, data[1] / scalar);
}

Vector2 Vector2::operator-() const
{
	return Vector2(-data[0], -data[1]);
}

float Vector2::length() const
{
	return sqrtf(data[0] * data[0] + data[1] * data[1]);
}

float Vector2::lengthSquared() const
{
	return data[0] * data[0] + data[1] * data[1];
}

Vector2& Vector2::normalize()
{
	float len = length();
	if(len != 0.0f)
		return (*this) /= len;
	return *this;
}

Vector2 Vector2::normalized() const
{
	Vector2 tempVector(*this);
	return tempVector.normalize();
}

float Vector2::dotProduct(const Vector2& v) const
{
	return (data[0] * v.data[0] + data[1] * v.data[1]);
}
