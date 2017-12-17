#pragma once

class Vector2;

class Vector3
{
public:
	static const Vector3 LEFT;
	static const Vector3 RIGHT;
	static const Vector3 UP;
	static const Vector3 DOWN;
	static const Vector3 FORWARD;
	static const Vector3 BACK;

	float x_;
	float y_;
	float z_;

	Vector3();
	explicit Vector3(float value);
	explicit Vector3(float x, float y, float z);
	explicit Vector3(const Vector2& v, float z);

	inline const float* getPointer() { return &x_; }

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

