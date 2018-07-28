#include "vector3.h"

#include "../precompiled.h"

#include "../math/vector2.h"

const Vector3 LEFT(-1.0f, 0.0f, 0.0f);
const Vector3 RIGHT(1.0f, 0.0f, 0.0f);
const Vector3 UP(0.0f, 1.0f, 0.0f);
const Vector3 DOWN(0.0f, -1.0f, 0.0f);
const Vector3 FORWARD(0.0f, 0.0f, 1.0f);
const Vector3 BACK(0.0f, 0.0f, -1.0f);

Vector3::Vector3()
{
	x_ = 0.0f;
	y_ = 0.0f;
	z_ = 0.0f;
}

Vector3::Vector3(float value)
{
	x_ = value;
	y_ = value;
	z_ = value;
}

Vector3::Vector3(float x, float y, float z)
{
	x_ = x;
	y_ = y;
	z_ = z;
}

Vector3::Vector3(const Vector2& v, float z)
{
	x_ = v.x_;
	y_ = v.y_;
	z_ = z;
}
	
void Vector3::set(float x, float y, float z)
{
	x_ = x;
	y_ = y;
	z_ = z;
}

Vector3& Vector3::operator+=(const Vector3& v)
{
	x_ += v.x_;
	y_ += v.y_;
	z_ += v.z_;
	return *this;
}
	
Vector3& Vector3::operator-=(const Vector3& v)
{
	x_ -= v.x_;
	y_ -= v.y_;
	z_ -= v.z_;
	return *this;
}
	
Vector3& Vector3::operator*=(const float& scalar)
{
	x_ *= scalar;
	y_ *= scalar;
	z_ *= scalar;
	return *this;
}
	
Vector3& Vector3::operator/=(const float& scalar)
{
	x_ /= scalar;
	y_ /= scalar;
	z_ /= scalar;
	return *this;
}
	
Vector3 Vector3::operator+(const Vector3& v) const
{
	return Vector3(x_ + v.x_, y_ + v.y_, z_ + v.z_);
}
	
Vector3 Vector3::operator-(const Vector3& v) const
{
	return Vector3(x_ - v.x_, y_ - v.y_, z_ - v.z_);
}
	
Vector3 Vector3::operator*(const float& scalar) const
{
	return Vector3(x_ * scalar, y_ * scalar, z_ * scalar);
}

Vector3 Vector3::operator/(const float& scalar) const
{
	return Vector3(x_ / scalar, y_ / scalar, z_ / scalar);
}
	
Vector3 Vector3::operator-() const
{
	return Vector3(-x_, -y_, -z_);
}
	
float Vector3::length() const
{
	return sqrtf(x_ * x_ + y_ * y_ + z_ * z_);
}
	
float Vector3::lengthSquared() const
{
	return x_ * x_ + y_ * y_ + z_ * z_;
}

Vector3 Vector3::abs() const
{
	return Vector3(std::fabs(x_), std::fabs(y_), std::fabs(z_));
}
	
Vector3& Vector3::normalize()
{
	float len = length();
	if (len != 0.0f)
		return (*this) /= len;
	return *this;
}
	
Vector3 Vector3::normalized() const
{
	Vector3 tempVector(*this);
	return tempVector.normalize();
}
	
float Vector3::dotProduct(const Vector3& v) const
{
	return x_ * v.x_ + y_ * v.y_ + z_ * v.z_;
}
	
Vector3 Vector3::crossProduct(const Vector3& v) const
{
	return Vector3(y_ * v.z_ - z_ * v.y_, z_ * v.x_ - x_ * v.z_, x_ * v.y_ - y_ * v.x_);
}

std::string Vector3::toString() const
{
	return std::to_string(x_) + " " + std::to_string(y_) + " " + std::to_string(z_);
}
