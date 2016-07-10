#pragma once

#include "vector3.h"

namespace ximath
{
	class Matrix3
	{
	public:
		static const Matrix3 identity;

		Matrix3();
		explicit Matrix3(float value);
		explicit Matrix3(const Vector3 v1, const Vector3 v2, const Vector3 v3);

		explicit Matrix3(float data00, float data01, float data02,
						float data10, float data11, float data12,
						float data20, float data21, float data22);

		Matrix3& operator+=(const Matrix3& m);
		Matrix3& operator-=(const Matrix3& m);
		Matrix3& operator*=(const Matrix3& m);
		Matrix3& operator*=(const float& value);
		Matrix3& operator/=(const float& value);

		Matrix3 operator+(const Matrix3& m) const;
		Matrix3 operator-(const Matrix3& m) const;
		Matrix3 operator*(const Matrix3& m) const;
		Matrix3 operator*(const float& value) const;
		Matrix3 operator/(const float& value) const;

		Matrix3 operator-() const;

		Vector3 operator*(const Vector3& v) const;

		Vector3& operator[](const unsigned int i);
		const Vector3& operator[](const unsigned int i) const;
		
		Vector3 getColumn(const unsigned int i) const;

		bool operator==(const Matrix3& m) const;
		bool operator!=(const Matrix3& m) const;

		float determinant() const;

		Matrix3& invert();
		Matrix3 inverted() const;

		Matrix3& transpose();
		Matrix3 transposed() const;

		static Matrix3 rotationXMatrix(float angle);
		static Matrix3 rotationYMatrix(float angle);
		static Matrix3 rotationZMatrix(float angle);

		static Matrix3 rotationMatrix(float angle, float x, float y, float z);
		static Matrix3 rotationMatrix(float angle, Vector3 axis);

	private:
		Vector3 data[3];

		static void multiplicationHelper(const Matrix3& m1, const Matrix3& m2, Matrix3* m_out);
	};

	Matrix3 operator*(const float& value, const Matrix3& m);
}