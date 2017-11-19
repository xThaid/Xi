#pragma once

namespace ximath
{
	class Vector2;

	class Vector3
	{
	public:
		static const Vector3 axisX;
		static const Vector3 axisY;
		static const Vector3 axisZ;

		float x, y, z;

		Vector3();
		explicit Vector3(float value);
		explicit Vector3(float x, float y, float z);
		explicit Vector3(const Vector2& v, float z);

		void set(float x, float y, float z);

		Vector2 xy() const;

		Vector3& operator+=(const Vector3& v);
		Vector3& operator-=(const Vector3& v);
		Vector3& operator*=(const Vector3& v);
		Vector3& operator*=(const float& value);
		Vector3& operator/=(const Vector3& v);
		Vector3& operator/=(const float& value);

		Vector3 operator+(const Vector3& v) const;
		Vector3 operator-(const Vector3& v) const;
		Vector3 operator*(const Vector3& v) const;
		Vector3 operator*(const float& value) const;
		Vector3 operator/(const Vector3& v) const;
		Vector3 operator/(const float& value) const;

		Vector3 operator-() const;

		float& operator[](const unsigned int i);
		const float& operator[](const unsigned int i) const;

		bool operator==(const Vector3& v) const;
		bool operator!=(const Vector3& v) const;

		float length() const;
		float lengthSquared() const;

		Vector3& normalize();
		Vector3 normalized() const;

		float dotProduct(const Vector3& v) const;
		Vector3 crossProduct(const Vector3& v) const;
	};

	Vector3 operator*(const float& value, const Vector3& v);

	Vector3 normal(const Vector3& v);

	float dot(const Vector3& v1, const Vector3& v2);
	Vector3 cross(const Vector3& v1, const Vector3& v2);
}
