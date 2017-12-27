#include "vector2.h"

#include "../precompiled.h"

Vector2::Vector2()
{
	x_ = 0.0f;
	y_ = 0.0f;
}

Vector2::Vector2(float value)
{
	x_ = value;
	y_ = value;
}

Vector2::Vector2(float x, float y)
{
	x_ = x;
	y_ = y;
}

void Vector2::set(float x, float y)
{
	x_ = x;
	y_ = y;
}

Vector2& Vector2::operator+=(const Vector2& v)
{
	x_ += v.x_;
	y_ += v.y_;
	return *this;
}

Vector2& Vector2::operator-=(const Vector2& v)
{
	x_ -= v.x_;
	y_ -= v.y_;
	return *this;
}

Vector2& Vector2::operator*=(const float& scalar)
{
	x_ *= scalar;
	y_ *= scalar;
	return *this;
}

Vector2& Vector2::operator/=(const float& scalar)
{
	x_ /= scalar;
	y_ /= scalar;
	return *this;
}
	
Vector2 Vector2::operator+(const Vector2& v) const
{
	return Vector2(x_ + v.x_, y_ + v.y_);
}

Vector2 Vector2::operator-(const Vector2& v) const
{
	return Vector2(x_ - v.x_, y_ - v.y_);
}

Vector2 Vector2::operator*(const float& scalar) const
{
	return Vector2(x_ * scalar, y_ * scalar);
}

Vector2 Vector2::operator/(const float& scalar) const
{
	return Vector2(x_ / scalar, y_ / scalar);
}

Vector2 Vector2::operator-() const
{
	return Vector2(-x_, -y_);
}

float Vector2::length() const
{
	return sqrtf(x_ * x_ + y_ * y_);
}

float Vector2::lengthSquared() const
{
	return x_ * x_ + y_ * y_;
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
	return (x_ * v.x_ + y_ * v.y_);
}

IntVector2::IntVector2() :
	x_(0),
	y_(0)
{
}

IntVector2::IntVector2(int x, int y) :
	x_(x),
	y_(y)
{
}

bool IntVector2::operator==(const IntVector2& rhs)
{
	return x_ == rhs.x_ && y_ == rhs.y_;
}

bool IntVector2::operator!=(const IntVector2& rhs)
{
	return !operator==(rhs);
}
