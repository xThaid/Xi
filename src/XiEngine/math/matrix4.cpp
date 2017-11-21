#include "matrix4.h"

#include <math.h>

#include "vector3.h"
#include "vector4.h"

namespace xim
{
	Matrix4::Matrix4()
	{
		data[0] = 1.0f; data[4] = 0.0f; data[8]  = 0.0f; data[12] = 0.0f;
		data[1] = 0.0f; data[5] = 1.0f; data[9]  = 0.0f; data[13] = 0.0f;
		data[2] = 0.0f; data[6] = 0.0f; data[10] = 1.0f; data[14] = 0.0f;
		data[3] = 0.0f; data[7] = 0.0f; data[11] = 0.0f; data[15] = 1.0f;
	}

	void Matrix4::copy(const Matrix4& m)
	{
		data[0] = m.data[0]; data[4] = m.data[4]; data[8] = m.data[8]; data[12] = m.data[12];
		data[1] = m.data[1]; data[5] = m.data[5]; data[9] = m.data[9]; data[13] = m.data[13];
		data[2] = m.data[2]; data[6] = m.data[6]; data[10] = m.data[10]; data[14] = m.data[14];
		data[3] = m.data[3]; data[7] = m.data[7]; data[11] = m.data[11]; data[15] = m.data[15];
	}

	Matrix4& Matrix4::operator*=(const Matrix4& m)
	{
		Matrix4 result = (*this) * m;
		copy(result);
		return *this;
	}

	Matrix4 Matrix4::operator*(const Matrix4& m) const
	{
		Matrix4 result;
		
		result.data[0] = data[0] * m.data[0] + data[4] * m.data[1] + data[8] * m.data[2] + data[12] * m.data[3];
		result.data[1] = data[1] * m.data[0] + data[5] * m.data[1] + data[9] * m.data[2] + data[13] * m.data[3];
		result.data[2] = data[2] * m.data[0] + data[6] * m.data[1] + data[10] * m.data[2] + data[14] * m.data[3];
		result.data[3] = data[3] * m.data[0] + data[7] * m.data[1] + data[11] * m.data[2] + data[15] * m.data[3];

		result.data[4] = data[0] * m.data[4] + data[4] * m.data[5] + data[8] * m.data[6] + data[12] * m.data[7];
		result.data[5] = data[1] * m.data[4] + data[5] * m.data[5] + data[9] * m.data[6] + data[13] * m.data[7];
		result.data[6] = data[2] * m.data[4] + data[6] * m.data[5] + data[10] * m.data[6] + data[14] * m.data[7];
		result.data[7] = data[3] * m.data[4] + data[7] * m.data[5] + data[11] * m.data[6] + data[15] * m.data[7];

		result.data[8] = data[0] * m.data[8] + data[4] * m.data[9] + data[8] * m.data[10] + data[12] * m.data[11];
		result.data[9] = data[1] * m.data[8] + data[5] * m.data[9] + data[9] * m.data[10] + data[13] * m.data[11];
		result.data[10] = data[2] * m.data[8] + data[6] * m.data[9] + data[10] * m.data[10] + data[14] * m.data[11];
		result.data[11] = data[3] * m.data[8] + data[7] * m.data[9] + data[11] * m.data[10] + data[15] * m.data[11];

		result.data[12] = data[0] * m.data[12] + data[4] * m.data[13] + data[8] * m.data[14] + data[12] * m.data[15];
		result.data[13] = data[1] * m.data[12] + data[5] * m.data[13] + data[9] * m.data[14] + data[13] * m.data[15];
		result.data[14] = data[2] * m.data[12] + data[6] * m.data[13] + data[10] * m.data[14] + data[14] * m.data[15];
		result.data[15] = data[3] * m.data[12] + data[7] * m.data[13] + data[11] * m.data[14] + data[15] * m.data[15];

		return result;
	}

	Vector3 Matrix4::operator*(const Vector3& v) const
	{
		Vector4 result = *this * Vector4(v, 1.0f);
		return result.xyz();
	}

	Vector4 Matrix4::operator*(const Vector4& v) const
	{
		Vector4 result;
	
		result.data[0] = data[0] * v.data[0] + data[4] * v.data[1] + data[8] * v.data[2] + data[12] * v.data[3];
		result.data[1] = data[1] * v.data[0] + data[5] * v.data[1] + data[9] * v.data[2] + data[13] * v.data[3];
		result.data[2] = data[2] * v.data[0] + data[6] * v.data[1] + data[10] * v.data[2] + data[14] * v.data[3];
		result.data[3] = data[3] * v.data[0] + data[7] * v.data[1] + data[11] * v.data[2] + data[15] * v.data[3];
		
		return result;
	}

	Matrix4& Matrix4::transpose()
	{
		float temp;
		temp = data[1]; data[1] = data[4]; data[4] = temp;
		temp = data[2]; data[2] = data[8]; data[8] = temp;
		temp = data[3]; data[3] = data[12]; data[12] = temp;
		temp = data[6]; data[6] = data[9]; data[9] = temp;
		temp = data[7]; data[7] = data[13]; data[13] = temp;
		temp = data[11]; data[11] = data[14]; data[14] = temp;
		return *this;
	}

	Matrix4 Matrix4::transposed() const
	{
		Matrix4 tempMatrix(*this);
		return tempMatrix.transpose();
	}

	Matrix4& Matrix4::translate(float x, float y, float z)
	{
		return translate(Vector3(x, y, z));
	}

	Matrix4& Matrix4::translate(const Vector3& v)
	{
		data[12] = data[0] * v.data[0] + data[4] * v.data[1] + data[8] * v.data[2] + data[12];
		data[13] = data[1] * v.data[0] + data[5] * v.data[1] + data[9] * v.data[2] + data[13];
		data[14] = data[2] * v.data[0] + data[6] * v.data[1] + data[10] * v.data[2] + data[14];
		return *this;
	}

	Matrix4& Matrix4::scale(float x, float y, float z)
	{
		return scale(Vector3(x, y, z));
	}

	Matrix4& Matrix4::scale(const Vector3& v)
	{
		data[0] = data[0] * v.data[0];
		data[1] = data[1] * v.data[0];
		data[2] = data[2] * v.data[0];
		data[3] = data[3] * v.data[0];

		data[4] = data[4] * v.data[1];
		data[5] = data[5] * v.data[1];
		data[6] = data[6] * v.data[1];
		data[7] = data[7] * v.data[1];
		
		data[8] = data[8] * v.data[2];
		data[9] = data[9] * v.data[2];
		data[10] = data[10] * v.data[2];
		data[11] = data[11] * v.data[2];

		return *this;
	}

	Matrix4& Matrix4::rotateX(float angle)
	{
		Matrix4 m = rotationXMatrix(angle);
		(*this) *= m;
		return *this;
	}

	Matrix4& Matrix4::rotateY(float angle)
	{
		Matrix4 m = rotationYMatrix(angle);
		(*this) *= m;
		return *this;
	}

	Matrix4& Matrix4::rotateZ(float angle)
	{
		Matrix4 m = rotationZMatrix(angle);
		(*this) *= m;
		return *this;
	}

	Matrix4& Matrix4::rotate(float angle, float x, float y, float z)
	{
		return rotate(angle, Vector3(x, y, z));
	}

	Matrix4& Matrix4::rotate(float angle, const Vector3& v)
	{
		Matrix4 m = rotationMatrix(angle, v);
		(*this) *= m;
		return *this;
	}

	Matrix4 Matrix4::rotationXMatrix(float angle)
	{
		float c = cosf(angle);
		float s = sinf(angle);
		Matrix4 result;
		result.data[5] = c;
		result.data[6] = s;
		result.data[9] = -s;
		result.data[10] = c;
		return result;
	}

	Matrix4 Matrix4::rotationYMatrix(float angle)
	{
		float c = cosf(angle);
		float s = sinf(angle);
		Matrix4 result;
		result.data[0] = c;
		result.data[2] = -s;
		result.data[8] = s;
		result.data[10] = c;
		return result;
	}

	Matrix4 Matrix4::rotationZMatrix(float angle)
	{
		float c = cosf(angle);
		float s = sinf(angle);
		Matrix4 result;
		result.data[0] = c;
		result.data[1] = s;
		result.data[4] = -s;
		result.data[5] = c;
		return result;
	}

	Matrix4 Matrix4::rotationMatrix(float angle, float x, float y, float z)
	{
		return rotationMatrix(angle, Vector3(x, y, z));
	}

	Matrix4 Matrix4::rotationMatrix(float angle, Vector3 v)
	{
		float c = cosf(angle);
		float s = sinf(angle);

		Vector3 axis = v.normalized();
		Vector3 temp = axis * (1.0f - c);

		Matrix4 result;

		result.data[0] = c + temp.data[0] * axis.data[0];
		result.data[1] = 0 + temp.data[0] * axis.data[1] + axis.data[2] * s;
		result.data[2] = 0 + temp.data[0] * axis.data[2] - axis.data[1] * s;

		result.data[4] = 0 + temp.data[1] * axis.data[0] - axis.data[2] * s;
		result.data[5] = c + temp.data[1] * axis.data[1];
		result.data[6] = 0 + temp.data[1] * axis.data[2] + axis.data[0] * s;

		result.data[8] = 0 + temp.data[2] * axis.data[0] + axis.data[1] * s;
		result.data[9] = 0 + temp.data[2] * axis.data[1] - axis.data[0] * s;
		result.data[10] = c + temp.data[2] * axis.data[2];

		return result;
	}

	Matrix4 Matrix4::translationMatrix(float x, float y, float z)
	{
		return translationMatrix(Vector3(x, y, z));
	}

	Matrix4 Matrix4::translationMatrix(Vector3 v)
	{
		Matrix4 m;
		m.data[12] = v.data[0];
		m.data[13] = v.data[1];
		m.data[14] = v.data[2];

		return m;
	}

	Matrix4 Matrix4::scaleMatrix(float x, float y, float z)
	{
		return scaleMatrix(Vector3(x, y, z));
	}

	Matrix4 Matrix4::scaleMatrix(Vector3 v)
	{
		Matrix4 m;
		m.data[0] = v.data[0];
		m.data[5] = v.data[1];
		m.data[10] = v.data[2];
		return m;
	}

	Matrix4 perspective(float fovy, float aspect, float znear, float zfar)
	{
		Matrix4 m;
		float tg = tanf(fovy / 2.0f);
		float dist = zfar - znear;

		m.data[0] = 1.0f / (tg * aspect);
		m.data[5] = 1.0f / tg;
		m.data[10] = -(zfar + znear) / dist;
		m.data[11] = -1.0f;
		m.data[14] = -2.0f * zfar * znear / dist;
		m.data[15] = 0.0f;

		return m;
	}

	Matrix4 ortho(float left, float right, float bottom, float top, float znear, float zfar)
	{
		Matrix4 m;
		m.data[0] = 2.0f / (right - left);
		m.data[5] = 2.0f / (top - bottom);
		m.data[10] = -2.0f / (zfar - znear);
		m.data[12] = -((right + left) / (right - left));
		m.data[13] = -((top + bottom) / (top - bottom));
		m.data[14] = -((zfar + znear) / (zfar - znear));
		m.data[15] = 1.0f;

		return m;
	}

	Matrix4 lookAt(const Vector3& eye, const Vector3& target, const Vector3& up)
	{
		Vector3 zAxis = (eye - target).normalized();
		Vector3 xAxis = up.crossProduct(zAxis).normalized();
		Vector3 yAxis = zAxis.crossProduct(xAxis);

		Matrix4 res;
		res.data[0] = xAxis.data[0];
		res.data[4] = xAxis.data[1];
		res.data[8] = xAxis.data[2];

		res.data[1] = yAxis.data[0];
		res.data[5] = yAxis.data[1];
		res.data[9] = yAxis.data[2];

		res.data[2] = zAxis.data[0];
		res.data[6] = zAxis.data[1];
		res.data[10] = zAxis.data[2];

		res.data[12] = -eye.dotProduct(xAxis);
		res.data[13] = -eye.dotProduct(yAxis);
		res.data[14] = -eye.dotProduct(zAxis);
		res.data[15] = 1.0f;

		return res;
	}
}