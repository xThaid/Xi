#pragma once

#include "vector4.h"

namespace ximath
{
	class Matrix3;
	class Quaternion;
	class EulerAngles;

	class Matrix4
	{
	public:
		static const Matrix4 identity;

		Matrix4();
		explicit Matrix4(float value);
		explicit Matrix4(const Vector4 v1, const Vector4 v2, const Vector4 v3, const Vector4 v4);
		explicit Matrix4(const Matrix3& m);

		explicit Matrix4(float data00, float data01, float data02,
			float data10, float data11, float data12,
			float data20, float data21, float data22);

		explicit Matrix4(float data00, float data01, float data02, float data03,
			float data10, float data11, float data12, float data13,
			float data20, float data21, float data22, float data23,
			float data30, float data31, float data32, float data33);

		Matrix4& operator+=(const Matrix4& m);
		Matrix4& operator-=(const Matrix4& m);
		Matrix4& operator*=(const Matrix4& m);
		Matrix4& operator*=(const Matrix3& m);
		Matrix4& operator*=(const float& value);
		Matrix4& operator/=(const float& value);

		Matrix4 operator+(const Matrix4& m) const;
		Matrix4 operator-(const Matrix4& m) const;
		Matrix4 operator*(const Matrix4& m) const;
		Matrix4 operator*(const Matrix3& m) const;
		Matrix4 operator*(const float& value) const;
		Matrix4 operator/(const float& value) const;

		Matrix4 operator-() const;

		Vector4 operator*(const Vector4& v) const;

		Vector4& operator[](const unsigned int i);
		const Vector4& operator[](const unsigned int i) const;

		Vector4 getColumn(const unsigned int i) const;

		bool operator==(const Matrix4& m) const;
		bool operator!=(const Matrix4& m) const;

		//Matrix4& invert();
		//Matrix4 inverted() const;

		Matrix4& transpose();
		Matrix4 transposed() const;

		Matrix4& translate(float x, float y, float z);
		Matrix4& translate(const Vector3& v);

		Matrix4& scale(float x, float y, float z);
		Matrix4& scale(const Vector3& v);

		Matrix4& rotateX(float angle);
		Matrix4& rotateY(float angle);
		Matrix4& rotateZ(float angle);

		Matrix4& rotate(float angle, float x, float y, float z);
		Matrix4& rotate(float angle, const Vector3& v);

		Matrix4& rotate(const Matrix3& m);
		Matrix4& rotate(const EulerAngles& angles);
		Matrix4& rotate(const Quaternion& quat);

		static Matrix4 rotationXMatrix(float angle);
		static Matrix4 rotationYMatrix(float angle);
		static Matrix4 rotationZMatrix(float angle);

		static Matrix4 rotationMatrix(float angle, float x, float y, float z);
		static Matrix4 rotationMatrix(float angle, Vector3 axis);

		static Matrix4 translationMatrix(float x, float y, float z);
		static Matrix4 translationMatrix(Vector3 v);

		static Matrix4 scaleMatrix(float x, float y, float z);
		static Matrix4 scaleMatrix(Vector3 v);
		
	private:
		Vector4 data[4];

		static void multiplicationHelper(const Matrix4& m1, const Matrix4& m2, Matrix4* m_out);
		static void multiplicationHelper(const Matrix4& m1, const Matrix3& m2, Matrix4* m_out);
	};

	Matrix4 operator*(const float& value, const Matrix4& m);

	Matrix4 perspective(float fovy, float aspect, float znear, float zfar);
	Matrix4 ortho(float left, float right, float bottom, float top, float znear, float zfar);
	Matrix4 lookAt(const Vector3& eye, const Vector3& at, const Vector3& up);
}