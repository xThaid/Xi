#pragma once

namespace ximath
{
	class Vector3;

	class Vector4
	{
	public:
		float x, y, z, w;

		Vector4();
		explicit Vector4(float value);
		explicit Vector4(float x, float y, float z, float w);
		explicit Vector4(const Vector3& v, float w);

		void set(float x, float y, float z, float w);

		Vector3 xyz() const;

		Vector4& operator+=(const Vector4& v);
		Vector4& operator-=(const Vector4& v);
		Vector4& operator*=(const Vector4& v);
		Vector4& operator*=(const float& value);
		Vector4& operator/=(const Vector4& v);
		Vector4& operator/=(const float& value);

		Vector4 operator+(const Vector4& v) const;
		Vector4 operator-(const Vector4& v) const;
		Vector4 operator*(const Vector4& v) const;
		Vector4 operator*(const float& value) const;
		Vector4 operator/(const Vector4& v) const;
		Vector4 operator/(const float& value) const;

		Vector4 operator-() const;

		float& operator[](const unsigned int i);
		const float& operator[](const unsigned int i) const;

		bool operator==(const Vector4& v) const;
		bool operator!=(const Vector4& v) const;

		float length() const;
		float lengthSquared() const;

		Vector4& normalize();
		Vector4 normalized() const;

		float dotProduct(const Vector4& v) const;
	};

	Vector4 operator*(const float& value, const Vector4& v);

	Vector4 normal(const Vector4& v);

	float dot(const Vector4& v1, const Vector4& v2);
}
