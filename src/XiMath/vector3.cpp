#include "vector3.h"

#include <math.h>
#include <stdexcept>

#include "vector2.h"

namespace ximath
{
	const Vector3 Vector3::axisX = Vector3(1.0f, 0.0f, 0.0f);
	const Vector3 Vector3::axisY = Vector3(0.0f, 1.0f, 0.0f);
	const Vector3 Vector3::axisZ = Vector3(0.0f, 0.0f, 1.0f);

	Vector3::Vector3() : x(0.0f), y(0.0f), z(0.0f) {}
	Vector3::Vector3(float value) : x(value), y(value) {}
	Vector3::Vector3(float x, float y, float z) : x(x), y(y), z(z) {}
	Vector3::Vector3(const Vector2& v, float z) : x(v.x), y(v.y), z(z) {}
	
	void Vector3::set(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	Vector2 Vector3::xy() const
	{
		return Vector2(x, y);
	}
	
	Vector3& Vector3::operator+=(const Vector3& v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}
	
	Vector3& Vector3::operator-=(const Vector3& v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return *this;
	}
	
	Vector3& Vector3::operator*=(const Vector3& v)
	{
		x *= v.x;
		y *= v.y;
		z *= v.z;
		return *this;
	}
	
	Vector3& Vector3::operator*=(const float& value)
	{
		x *= value;
		y *= value;
		z *= value;
		return *this;
	}
	
	Vector3& Vector3::operator/=(const Vector3& v)
	{
		x /= v.x;
		y /= v.y;
		z /= v.z;
		return *this;
	}
	
	Vector3& Vector3::operator/=(const float& value)
	{
		x /= value;
		y /= value;
		z /= value;
		return *this;
	}
	
	Vector3 Vector3::operator+(const Vector3& v) const
	{
		return Vector3(x + v.x, y + v.y, z + v.z);
	}
	
	Vector3 Vector3::operator-(const Vector3& v) const
	{
		return Vector3(x - v.x, y - v.y, z - v.z);
	}
	
	Vector3 Vector3::operator*(const Vector3& v) const
	{
		return Vector3(x * v.x, y * v.y, z * v.z);
	}
	
	Vector3 Vector3::operator*(const float& value) const
	{
		return Vector3(x * value, y * value, z * value);
	}
	
	Vector3 Vector3::operator/(const Vector3& v) const
	{
		return Vector3(x / v.x, y / v.y, z / v.z);
	}

	Vector3 Vector3::operator/(const float& value) const
	{
		return Vector3(x / value, y / value, z / value);
	}
	
	Vector3 Vector3::operator-() const
	{
		return Vector3(-x, -y, -z);
	}

	float& Vector3::operator[](const unsigned int i)
	{
		if (i == 0) return x;
		if (i == 1) return y;
		if (i == 2) return z;

		throw std::out_of_range("out of range // TODO");
	}

	const float& Vector3::operator[](const unsigned int i) const
	{
		if (i == 0) return x;
		if (i == 1) return y;
		if (i == 2) return z;

		throw std::out_of_range("out of range // TODO");
	}
	
	bool Vector3::operator==(const Vector3& v) const
	{
		return (x == v.x && y == v.y && z == v.z);
	}
	
	bool Vector3::operator!=(const Vector3& v) const
	{
		return !(x == v.x && y == v.y && z == v.z);
	}
	
	float Vector3::length() const
	{
		return static_cast<float>(sqrt(lengthSquared()));
	}
	
	float Vector3::lengthSquared() const
	{
		return x * x + y * y + z * z;
	}
	
	Vector3& Vector3::normalize()
	{
		float length = this->length();
		if (length != 0.0f)
			return (*this) /= length;
		return *this;
	}
	
	Vector3 Vector3::normalized() const
	{
		Vector3 tempVector(*this);
		return tempVector.normalize();
	}
	
	float Vector3::dotProduct(const Vector3& v) const
	{
		return (x * v.x + y * v.y + z * v.z);
	}
	
	Vector3 Vector3::crossProduct(const Vector3& v) const
	{
		return Vector3(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
	}

	Vector3 operator*(const float& value, const Vector3& v)
	{
		return v * value;
	}

	Vector3 normal(const Vector3& v)
	{
		return v.normalized();
	}
	
	float dot(const Vector3& v1, const Vector3& v2)
	{
		return v1.dotProduct(v2);
	}
	
	Vector3 cross(const Vector3& v1, const Vector3& v2)
	{
		return v1.crossProduct(v2);
	}
}