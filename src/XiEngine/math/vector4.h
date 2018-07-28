#pragma once

#include <string>

class Vector3;

class Vector4
{
public:
	float x_;
	float y_;
	float z_;
	float w_;

	Vector4();
	explicit Vector4(float value);
	explicit Vector4(float x, float y, float z, float w);
	explicit Vector4(const Vector3& v, float w);

	inline const float* getPointer() const { return &x_; }

	void set(float x, float y, float z, float w);

	Vector3 xyz() const;

	Vector4& operator+=(const Vector4& v);
	Vector4& operator-=(const Vector4& v);
	Vector4& operator*=(const float& scalar);
	Vector4& operator/=(const float& scalar);

	Vector4 operator+(const Vector4& v) const;
	Vector4 operator-(const Vector4& v) const;
	Vector4 operator*(const float& scalar) const;
	Vector4 operator/(const float& scalar) const;

	Vector4 operator-() const;

	float length() const;
	float lengthSquared() const;

	Vector4& normalize();
	Vector4 normalized() const;

	float dotProduct(const Vector4& v) const;

	std::string toString() const;
};