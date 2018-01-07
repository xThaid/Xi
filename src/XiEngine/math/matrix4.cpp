#include "matrix4.h"

#include "../precompiled.h"

#include "../math/vector3.h"
#include "../math/vector4.h"

#include "../math/matrix3.h"
#include "../math/matrix3x4.h"

Matrix4::Matrix4()
{
	data[0] = 1.0f; data[4] = 0.0f; data[8]  = 0.0f; data[12] = 0.0f;
	data[1] = 0.0f; data[5] = 1.0f; data[9]  = 0.0f; data[13] = 0.0f;
	data[2] = 0.0f; data[6] = 0.0f; data[10] = 1.0f; data[14] = 0.0f;
	data[3] = 0.0f; data[7] = 0.0f; data[11] = 0.0f; data[15] = 1.0f;
}

Matrix4::Matrix4(const Matrix3& m)
{
	data[0] = m.data[0]; data[4] = m.data[3]; data[8] = m.data[6];   data[12] = 0.0f;
	data[1] = m.data[1]; data[5] = m.data[4]; data[9] = m.data[7];   data[13] = 0.0f;
	data[2] = m.data[2]; data[6] = m.data[5]; data[10] = m.data[8];  data[14] = 0.0f;
	data[3] = 0.0f;      data[7] = 0.0f;      data[11] = 0.0f;       data[15] = 1.0f;
}

Matrix4::Matrix4(const Matrix3x4& m)
{
	data[0] = m.data[0]; data[4] = m.data[3]; data[8] = m.data[6];   data[12] = m.data[9];
	data[1] = m.data[1]; data[5] = m.data[4]; data[9] = m.data[7];   data[13] = m.data[10];
	data[2] = m.data[2]; data[6] = m.data[5]; data[10] = m.data[8];  data[14] = m.data[11];
	data[3] = 0.0f;      data[7] = 0.0f;      data[11] = 0.0f;       data[15] = 1.0f;
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
	Vector3 result;

	float invW = 1.0f / (data[3] * v.x_ + data[7] * v.y_ + data[11] * v.z_ + data[15]);

	result.x_ = (data[0] * v.x_ + data[4] * v.y_ + data[8] * v.z_ + data[12]) * invW;
	result.y_ = (data[1] * v.x_ + data[5] * v.y_ + data[9] * v.z_ + data[13]) * invW;
	result.z_ = (data[2] * v.x_ + data[6] * v.y_ + data[10] * v.z_ + data[14]) * invW;

	return result;
}

Vector4 Matrix4::operator*(const Vector4& v) const
{
	Vector4 result;
	
	result.x_ = data[0] * v.x_ + data[4] * v.y_ + data[8] * v.z_ + data[12] * v.w_;
	result.y_ = data[1] * v.x_ + data[5] * v.y_ + data[9] * v.z_ + data[13] * v.w_;
	result.z_ = data[2] * v.x_ + data[6] * v.y_ + data[10] * v.z_ + data[14] * v.w_;
	result.w_ = data[3] * v.x_ + data[7] * v.y_ + data[11] * v.z_ + data[15] * v.w_;
		
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

Matrix4 Matrix4::orthoMatrix(float left, float right, float bottom, float top)
{
	Matrix4 m;
	m.data[0] = 2.0f / (right - left);
	m.data[5] = 2.0f / (top - bottom);
	m.data[10] = 1.0f;
	m.data[12] = -((right + left) / (right - left));
	m.data[13] = -((top + bottom) / (top - bottom));
	m.data[15] = 1.0f;

	return m;
}

Matrix4 Matrix4::orthoMatrix(float left, float right, float bottom, float top, float znear, float zfar)
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

Matrix4 Matrix4::lookAtMatrix(const Vector3& eye, const Vector3& target, const Vector3& up)
{
	Vector3 zAxis = (eye - target).normalized();
	Vector3 xAxis = up.crossProduct(zAxis).normalized();
	Vector3 yAxis = zAxis.crossProduct(xAxis);

	Matrix4 res;
	res.data[0] = xAxis.x_;
	res.data[4] = xAxis.y_;
	res.data[8] = xAxis.z_;

	res.data[1] = yAxis.x_;
	res.data[5] = yAxis.y_;
	res.data[9] = yAxis.z_;

	res.data[2] = zAxis.x_;
	res.data[6] = zAxis.y_;
	res.data[10] = zAxis.z_;

	res.data[12] = -eye.dotProduct(xAxis);
	res.data[13] = -eye.dotProduct(yAxis);
	res.data[14] = -eye.dotProduct(zAxis);
	res.data[15] = 1.0f;

	return res;
}