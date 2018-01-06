#include "vector4.h"

#include "../precompiled.h"

#include "../math/vector3.h"

Vector4::Vector4()
{
	x_ = 0.0f;
	y_ = 0.0f;
	z_ = 0.0f;
	w_ = 0.0f;
}

Vector4::Vector4(float value)
{
	x_ = value;
	y_ = value;
	z_ = value;
	w_ = value;
}

Vector4::Vector4(float x, float y, float z, float w)
{
	x_ = x;
	y_ = y;
	z_ = z;
	w_ = w;
}

Vector4::Vector4(const Vector3& v, float w)
{
	x_ = v.x_;
	y_ = v.y_;
	z_ = v.z_;
	w_ = w;
}

void Vector4::set(float x, float y, float z, float w)
{
	x_ = x;
	y_ = y;
	z_ = z;
	w_ = w;
}
	
Vector3 Vector4::xyz() const
{
	return Vector3(x_, y_, z_);
}
	
Vector4& Vector4::operator+=(const Vector4& v)
{
	x_ += v.x_;
	y_ += v.y_;
	z_ += v.z_;
	w_ += v.w_;
	return *this;
}
	
Vector4& Vector4::operator-=(const Vector4& v)
{
	x_ -= v.x_;
	y_ -= v.y_;
	z_ -= v.z_;
	w_ -= v.w_;
	return *this;
}
	
Vector4& Vector4::operator*=(const float& scalar)
{
	x_ *= scalar;
	y_ *= scalar;
	z_ *= scalar;
	w_ *= scalar;
	return *this;
}
	
Vector4& Vector4::operator/=(const float& scalar)
{
	x_ /= scalar;
	y_ /= scalar;
	z_ /= scalar;
	w_ /= scalar;
	return *this;
}
	
Vector4 Vector4::operator+(const Vector4& v) const
{
	return Vector4(x_ + v.x_, y_ + v.y_, z_ + v.z_, w_ + v.w_);
}
	
Vector4 Vector4::operator-(const Vector4& v) const
{
	return Vector4(x_ - v.x_, y_ - v.y_, z_ - v.z_, w_ - v.w_);
}
	
Vector4 Vector4::operator*(const float& scalar) const
{
	return Vector4(x_ * scalar, y_ * scalar, z_ * scalar, w_ * scalar);
}
	
Vector4 Vector4::operator/(const float& scalar) const
{
	return Vector4(x_ / scalar, y_ / scalar, z_ / scalar, w_ / scalar);
}
	
Vector4 Vector4::operator-() const
{
	return Vector4(-x_, -y_, -z_, -w_);
}
	
float Vector4::length() const
{
	return sqrtf(x_ * x_ + y_ * y_ + z_ * z_ + w_ * w_);
}
	
float Vector4::lengthSquared() const
{
	return x_ * x_ + y_ * y_ + z_ * z_ + w_ * w_;
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
	return x_ * v.x_ + y_ * v.y_ + z_ * v.z_ + w_ * v.w_;
}

std::string Vector4::toString() const
{
	return std::to_string(x_) + " " + std::to_string(y_) + " " + std::to_string(z_) + " " + std::to_string(w_);
}
