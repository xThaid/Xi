#pragma once


class Vector2
{
public:
	float data[2];

	Vector2();
	explicit Vector2(float value);
	explicit Vector2(float x, float y);

	inline float x() { return data[0]; }
	inline float y() { return data[1]; }

	inline const float* getPointer() { return &data[0]; }

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
