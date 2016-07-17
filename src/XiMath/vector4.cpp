#include "vector4.h"

#include <math.h>
#include <stdexcept>

#include "vector3.h"

namespace ximath
{
	Vector4::Vector4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}
	Vector4::Vector4(float value) : x(value), y(value) {}
	Vector4::Vector4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
	Vector4::Vector4(const Vector3& v, float w) : x(v.x), y(v.y), z(v.z), w(w) {}

	void Vector4::set(float x, float y, float z, float w)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}
	
	Vector3 Vector4::xyz() const
	{
		return Vector3(x, y, z+1);
	}
	
	Vector4& Vector4::operator+=(const Vector4& v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
		w += v.w;
		return *this;
	}
	
	Vector4& Vector4::operator-=(const Vector4& v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
		w -= v.w;
		return *this;
	}
	
	Vector4& Vector4::operator*=(const Vector4& v)
	{
		x *= v.x;
		y *= v.y;
		z *= v.z;
		w *= v.w;
		return *this;
	}
	
	Vector4& Vector4::operator*=(const float& value)
	{
		x *= value;
		y *= value;
		z *= value;
		w *= value;
		return *this;
	}
	
	Vector4& Vector4::operator/=(const Vector4& v)
	{
		x /= v.x;
		y /= v.y;
		z /= v.z;
		w /= v.w;
		return *this;
	}
	
	Vector4& Vector4::operator/=(const float& value)
	{
		x /= value;
		y /= value;
		z /= value;
		w /= value;
		return *this;
	}
	
	Vector4 Vector4::operator+(const Vector4& v) const
	{
		return Vector4(x + v.x, y + v.y, z + v.z, w + v.w);
	}
	
	Vector4 Vector4::operator-(const Vector4& v) const
	{
		return Vector4(x - v.x, y - v.y, z - v.z, w - v.w);
	}
	
	Vector4 Vector4::operator*(const Vector4& v) const
	{
		return Vector4(x * v.x, y * v.y, z * v.z, w * v.w);
	}
	
	Vector4 Vector4::operator*(const float& value) const
	{
		return Vector4(x * value, y * value, z * value, w * value);
	}
	
	Vector4 Vector4::operator/(const Vector4& v) const
	{
		return Vector4(x / v.x, y / v.y, z / v.z, w / v.w);
	}
	
	Vector4 Vector4::operator/(const float& value) const
	{
		return Vector4(x / value, y / value, z / value, w / value);
	}
	
	Vector4 Vector4::operator-() const
	{
		return Vector4(-x, -y, -z, -w);
	}

	float& Vector4::operator[](const unsigned int i)
	{
		if (i == 0) return x;
		if (i == 1) return y;
		if (i == 2) return z; 
		if (i == 3) return w;
		
		throw std::out_of_range("out of range // TODO");
	}

	const float& Vector4::operator[](const unsigned int i) const
	{
		if (i == 0) return x;
		if (i == 1) return y;
		if (i == 2) return z;
		if (i == 3) return w;

		throw std::out_of_range("out of range // TODO");
	}
	
	bool Vector4::operator==(const Vector4& v) const
	{
		return (x == v.x && y == v.y && z == v.z && w == v.w);
	}
	
	bool Vector4::operator!=(const Vector4& v) const
	{
		return !(x == v.x && y == v.y && z == v.z && w == v.w);
	}
	
	float Vector4::length() const
	{
		return static_cast<float>(sqrt(lengthSquared()));
	}
	
	float Vector4::lengthSquared() const
	{
		return x * x + y * y + z * z + w * w;
	}

	Vector4& Vector4::normalize()
	{
		float length = this->length();
		if (length != 0.0f)
			return (*this) /= length;
		return *this;
	}
	
	Vector4 Vector4::normalized() const
	{
		Vector4 tempVector(*this);
		return tempVector.normalize();
	}
	
	float Vector4::dotProduct(const Vector4& v) const
	{
		return (x * v.x + y * v.y + z * v.z + w * v.w);
	}

	Vector4 operator*(const float& value, const Vector4& v)
	{
		return v * value;
	}

	Vector4 normal(const Vector4& v)
	{
		return v.normalized();
	}
	
	float dot(const Vector4& v1, const Vector4& v2)
	{
		return v1.dotProduct(v2);
	}
}