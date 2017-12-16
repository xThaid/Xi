#pragma once


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
	Vector2& operator*=(const float& scalar);
	Vector2& operator/=(const float& scalar);

	Vector2 operator+(const Vector2& v) const;
	Vector2 operator-(const Vector2& v) const;
	Vector2 operator*(const float& scalar) const;
	Vector2 operator/(const float& scalar) const;

	Vector2 operator-() const;

	float length() const;
	float lengthSquared() const;

	Vector2& normalize();
	Vector2 normalized() const;

	float dotProduct(const Vector2& v) const;
};
