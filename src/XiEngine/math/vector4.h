#pragma once


class Vector3;

class Vector4
{
public:
	float data[4];

	Vector4();
	explicit Vector4(float value);
	explicit Vector4(float x, float y, float z, float w);
	explicit Vector4(const Vector3& v, float w);

	inline float x() { return data[0]; }
	inline float y() { return data[1]; }
	inline float z() { return data[2]; }
	inline float w() { return data[3]; }

	inline const float* getPointer() { return &data[0]; }

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
};