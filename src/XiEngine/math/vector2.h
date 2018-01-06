#pragma once

#include <string>

class IntVector2
{
public:
	int x_;
	int y_;

	IntVector2();
	IntVector2(int x, int y);

	bool operator==(const IntVector2& rhs);
	bool operator!=(const IntVector2& rhs);
};

class Vector2
{
public:
	float x_;
	float y_;

	Vector2();
	explicit Vector2(float value);
	explicit Vector2(float x, float y);

	inline const float* getPointer() { return &x_; }

	void set(float x, float y);

	Vector2& operator+=(const Vector2& v);
	Vector2& operator-=(const Vector2& v);
	Vector2& operator+=(float value);
	Vector2& operator-=(float value);
	Vector2& operator*=(const float& scalar);
	Vector2& operator/=(const float& scalar);

	Vector2 operator+(const Vector2& v) const;
	Vector2 operator-(const Vector2& v) const;
	Vector2 operator+(float value);
	Vector2 operator-(float value);
	Vector2 operator*(const float& scalar) const;
	Vector2 operator/(const float& scalar) const;

	Vector2 operator-() const;

	float length() const;
	float lengthSquared() const;

	Vector2& normalize();
	Vector2 normalized() const;

	float dotProduct(const Vector2& v) const;

	std::string toString() const;
};
