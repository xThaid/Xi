#include "vector2.h"

#include <math.h>
#include <stdexcept>

namespace ximath
{
	Vector2::Vector2() : x(0.0f), y(0.0f) {}
	Vector2::Vector2(float value) : x(value), y(value) {}
	Vector2::Vector2(float x, float y) : x(x), y(y) {}

	void Vector2::set(float x, float y)
	{
		this->x = x;
		this->y = y;
	}

	Vector2& Vector2::operator+=(const Vector2& v)
	{
		x += v.x;
		y += v.y;
		return *this;
	}

	Vector2& Vector2::operator-=(const Vector2& v)
	{
		x -= v.x;
		y -= v.y;
		return *this;
	}

	Vector2& Vector2::operator*=(const Vector2& v)
	{
		x *= v.x;
		y *= v.y;
		return *this;
	}

	Vector2& Vector2::operator*=(const float& value)
	{
		x *= value;
		y *= value;
		return *this;
	}

	Vector2& Vector2::operator/=(const Vector2& v)
	{
		x /= v.x;
		y /= v.y;
		return *this;
	}

	Vector2& Vector2::operator/=(const float& value)
	{
		x /= value;
		y /= value;
		return *this;
	}
	
	Vector2 Vector2::operator+(const Vector2& v) const
	{
		return Vector2(x + v.x, y + v.y);
	}

	Vector2 Vector2::operator-(const Vector2& v) const
	{
		return Vector2(x - v.x, y - v.y);
	}

	Vector2 Vector2::operator*(const Vector2& v) const
	{
		return Vector2(x * v.x, y * v.y);
	}

	Vector2 Vector2::operator*(const float& value) const
	{
		return Vector2(x * value, y * value);
	}

	Vector2 Vector2::operator/(const Vector2& v) const
	{
		return Vector2(x / v.x, y / v.y);
	}

	Vector2 Vector2::operator/(const float& value) const
	{
		return Vector2(x / value, y / value);
	}

	Vector2 Vector2::operator-() const
	{
		return Vector2(-x, -y);
	}

	float& Vector2::operator[](const unsigned int i)
	{
		if (i == 0) return x;
		if (i == 1) return y;

		throw std::out_of_range("out of range // TODO");
	}

	const float& Vector2::operator[](const unsigned int i) const
	{
		if (i == 0) return x;
		if (i == 1) return y;

		throw std::out_of_range("out of range // TODO");
	}

	bool Vector2::operator==(const Vector2& v) const
	{
		return (x == v.x && y == v.y);
	}

	bool Vector2::operator!=(const Vector2& v) const
	{
		return !(x == v.x && y == v.y);
	}

	float Vector2::length() const
	{
		return static_cast<float>(sqrt(lengthSquared()));
	}

	float Vector2::lengthSquared() const
	{
		return x * x + y * y;
	}

	Vector2& Vector2::normalize()
	{
		float length = this->length();
		if(length != 0.0f)
			return (*this) /= length;
		return *this;
	}

	Vector2 Vector2::normalized() const
	{
		Vector2 tempVector(*this);
		return tempVector.normalize();
	}

	float Vector2::dotProduct(const Vector2& v) const
	{
		return (x * v.x + y * v.y);
	}

	Vector2 operator*(const float& value, const Vector2& v)
	{
		return v * value;
	}

	Vector2 normal(const Vector2& v)
	{
		return v.normalized();
	}

	float dot(const Vector2& v1, const Vector2& v2)
	{
		return v1.dotProduct(v2);
	}
}