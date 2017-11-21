#include "vector3.h"

#include <math.h>

#include "vector2.h"

namespace xim
{
	Vector3::Vector3()
	{
		data[0] = 0.0f;
		data[1] = 0.0f;
		data[2] = 0.0f;
	}

	Vector3::Vector3(float value)
	{
		data[0] = value;
		data[1] = value;
		data[2] = value;
	}

	Vector3::Vector3(float x, float y, float z)
	{
		data[0] = x;
		data[1] = y;
		data[2] = z;
	}

	Vector3::Vector3(const Vector2& v, float z)
	{
		data[0] = v.data[0];
		data[1] = v.data[1];
		data[2] = z;
	}
	
	void Vector3::set(float x, float y, float z)
	{
		data[0] = x;
		data[1] = y;
		data[2] = z;
	}

	Vector3& Vector3::operator+=(const Vector3& v)
	{
		data[0] += v.data[0];
		data[1] += v.data[1];
		data[2] += v.data[2];
		return *this;
	}
	
	Vector3& Vector3::operator-=(const Vector3& v)
	{
		data[0] -= v.data[0];
		data[1] -= v.data[1];
		data[2] -= v.data[2];
		return *this;
	}
	
	Vector3& Vector3::operator*=(const float& scalar)
	{
		data[0] *= scalar;
		data[1] *= scalar;
		data[2] *= scalar;
		return *this;
	}
	
	Vector3& Vector3::operator/=(const float& scalar)
	{
		data[0] /= scalar;
		data[1] /= scalar;
		data[2] /= scalar;
		return *this;
	}
	
	Vector3 Vector3::operator+(const Vector3& v) const
	{
		return Vector3(data[0] + v.data[0], data[1] + v.data[1], data[2] + v.data[2]);
	}
	
	Vector3 Vector3::operator-(const Vector3& v) const
	{
		return Vector3(data[0] - v.data[0], data[1] - v.data[1], data[2] - v.data[2]);
	}
	
	Vector3 Vector3::operator*(const float& scalar) const
	{
		return Vector3(data[0] * scalar, data[1] * scalar, data[2] * scalar);
	}

	Vector3 Vector3::operator/(const float& scalar) const
	{
		return Vector3(data[0] / scalar, data[1] / scalar, data[2] / scalar);
	}
	
	Vector3 Vector3::operator-() const
	{
		return Vector3(-data[0], -data[1], -data[2]);
	}
	
	float Vector3::length() const
	{
		return sqrtf(data[0] * data[0] + data[1] * data[1] + data[2] * data[2]);
	}
	
	float Vector3::lengthSquared() const
	{
		return data[0] * data[0] + data[1] * data[1] + data[2] * data[2];
	}
	
	Vector3& Vector3::normalize()
	{
		float len = length();
		if (len != 0.0f)
			return (*this) /= len;
		return *this;
	}
	
	Vector3 Vector3::normalized() const
	{
		Vector3 tempVector(*this);
		return tempVector.normalize();
	}
	
	float Vector3::dotProduct(const Vector3& v) const
	{
		return data[0] * v.data[0] + data[1] * v.data[1] + data[2] * v.data[2];
	}
	
	Vector3 Vector3::crossProduct(const Vector3& v) const
	{
		return Vector3(data[1] * v.data[2] - data[2] * v.data[1], data[2] * v.data[0] - data[0] * v.data[2], data[0] * v.data[1] - data[1] * v.data[0]);
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