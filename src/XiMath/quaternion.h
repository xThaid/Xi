#pragma once

namespace ximath
{
	class Vector3;
	class Matrix3;
	class Matrix4;
	class EulerAngles;

	class Quaternion
	{
	public:
		static const Quaternion identity;

		float x, y, z, w;

		Quaternion();
		explicit Quaternion(Vector3 v, float w);
		explicit Quaternion(float x, float y, float z, float w);

		Quaternion& operator*=(const Quaternion& q);
		Quaternion& operator+=(const Quaternion& q);
		Quaternion& operator*=(const float& value);

		Quaternion operator*(const Quaternion& q) const;
		Quaternion operator+(const Quaternion& q) const;
		Quaternion operator*(const float& value) const;

		Quaternion operator-() const;

		bool operator==(const Quaternion& q) const;
		bool operator!=(const Quaternion& q) const;

		Matrix3 toMatrix3() const;
		Matrix4 toMatrix4() const;
		EulerAngles toEulerAngles() const;

		Quaternion& conjugate();
		Quaternion conjugated() const;

		Quaternion& normalize();
		Quaternion normalized() const;

		Quaternion& inverse();
		Quaternion inversed() const;

		float length() const;

		float dotProduct(const Quaternion& q) const;

		static Quaternion rotationX(float angle);
		static Quaternion rotationY(float angle);
		static Quaternion rotationZ(float angle);

		static Quaternion rotationAxis(float angle, float x, float y, float z);
		static Quaternion rotationAxis(float angle, Vector3 v);

		static Quaternion fromEulerAngles(const EulerAngles& a);

		static Quaternion difference(const Quaternion& q1, const Quaternion& q2);

		static Quaternion lerp(const Quaternion& q1, const Quaternion& q2, float t);
		static Quaternion slerp(const Quaternion& q1, const Quaternion& q2, float t);

	private:
		
	};
}