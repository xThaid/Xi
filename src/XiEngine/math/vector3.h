#pragma once


class Vector2;

class Vector3
{
public:
	float data[3];

	Vector3();
	explicit Vector3(float value);
	explicit Vector3(float x, float y, float z);
	explicit Vector3(const Vector2& v, float z);

	inline float x() const { return data[0]; }
	inline float y() const { return data[1]; }
	inline float z() const { return data[2]; }

	inline const float* getPointer() { return &data[0]; }

	void set(float x, float y, float z);

	Vector3& operator+=(const Vector3& v);
	Vector3& operator-=(const Vector3& v);
	Vector3& operator*=(const float& scalar);
	Vector3& operator/=(const float& scalar);

	Vector3 operator+(const Vector3& v) const;
	Vector3 operator-(const Vector3& v) const;
	Vector3 operator*(const float& value) const;
	Vector3 operator/(const float& value) const;

	Vector3 operator-() const;

	float length() const;
	float lengthSquared() const;

	Vector3& normalize();
	Vector3 normalized() const;

	float dotProduct(const Vector3& v) const;
	Vector3 crossProduct(const Vector3& v) const;
};

