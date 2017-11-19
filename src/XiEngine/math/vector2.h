#pragma once

namespace ximath
{
	class Vector2
	{
	public:
		float x, y;

		Vector2();
		explicit Vector2(float value);
		explicit Vector2(float x, float y);

		void set(float x, float y);

		Vector2& operator+=(const Vector2& v);
		Vector2& operator-=(const Vector2& v);
		Vector2& operator*=(const Vector2& v);
		Vector2& operator*=(const float& value);
		Vector2& operator/=(const Vector2& v);
		Vector2& operator/=(const float& value);

		Vector2 operator+(const Vector2& v) const;
		Vector2 operator-(const Vector2& v) const;
		Vector2 operator*(const Vector2& v) const;
		Vector2 operator*(const float& value) const;
		Vector2 operator/(const Vector2& v) const;
		Vector2 operator/(const float& value) const;

		Vector2 operator-() const;

		float& operator[](const unsigned int i);
		const float& operator[](const unsigned int i) const;

		bool operator==(const Vector2& v) const;
		bool operator!=(const Vector2& v) const;

		float length() const;
		float lengthSquared() const;

		Vector2& normalize();
		Vector2 normalized() const;

		float dotProduct(const Vector2& v) const;
	};

	Vector2 operator*(const float& value, const Vector2& v);
	
	Vector2 normal(const Vector2& v);

	float dot(const Vector2& v1, const Vector2& v2);
}
