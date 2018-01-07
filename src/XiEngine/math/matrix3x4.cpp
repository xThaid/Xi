#include "matrix3x4.h"

#include "../precompiled.h"

#include "../math/vector3.h"

#include "../math/matrix3.h"
#include "../math/matrix4.h"

Matrix3x4::Matrix3x4()
{
	data[0] = 1.0f; data[3] = 0.0f; data[6] = 0.0f; data[9] = 0.0f;
	data[1] = 0.0f; data[4] = 1.0f; data[7] = 0.0f; data[10] = 0.0f;
	data[2] = 0.0f; data[5] = 0.0f; data[8] = 1.0f; data[11] = 0.0f;
}

Matrix3x4::Matrix3x4(const Matrix3& m)
{
	data[0] = m.data[0]; data[3] = m.data[3]; data[6] = m.data[6]; data[9] = 0.0f;
	data[1] = m.data[1]; data[4] = m.data[4]; data[7] = m.data[7]; data[10] = 0.0f;
	data[2] = m.data[2]; data[5] = m.data[5]; data[8] = m.data[8]; data[11] = 0.0f;
}

Matrix3x4::Matrix3x4(const Matrix4& m)
{
	data[0] = m.data[0]; data[3] = m.data[4]; data[6] = m.data[8]; data[9] = m.data[12];
	data[1] = m.data[1]; data[4] = m.data[5]; data[7] = m.data[9]; data[10] = m.data[13];
	data[2] = m.data[2]; data[5] = m.data[6]; data[8] = m.data[10]; data[11] = m.data[14];
}

void Matrix3x4::copy(const Matrix3x4& m)
{
	data[0] = m.data[0]; data[3] = m.data[3]; data[6] = m.data[6]; data[9] = m.data[9];
	data[1] = m.data[1]; data[4] = m.data[4]; data[7] = m.data[7]; data[10] = m.data[10];
	data[2] = m.data[2]; data[5] = m.data[5]; data[8] = m.data[8]; data[11] = m.data[11];
}

Matrix3x4& Matrix3x4::operator*=(const Matrix3x4& m)
{
	Matrix3x4 result = (*this) * m;
	copy(result);
	return *this;
}

Matrix3x4 Matrix3x4::operator*(const Matrix3x4& m) const
{
	Matrix3x4 result;

	result.data[0] = data[0] * m.data[0] + data[3] * m.data[1] + data[6] * m.data[2];
	result.data[1] = data[1] * m.data[0] + data[4] * m.data[1] + data[7] * m.data[2];
	result.data[2] = data[2] * m.data[0] + data[5] * m.data[1] + data[8] * m.data[2];
	
	result.data[3] = data[0] * m.data[3] + data[3] * m.data[4] + data[6] * m.data[5];
	result.data[4] = data[1] * m.data[3] + data[4] * m.data[4] + data[7] * m.data[5];
	result.data[5] = data[2] * m.data[3] + data[5] * m.data[4] + data[8] * m.data[5];
	
	result.data[6] = data[0] * m.data[6] + data[3] * m.data[7] + data[6] * m.data[8];
	result.data[7] = data[1] * m.data[6] + data[4] * m.data[7] + data[7] * m.data[8];
	result.data[8] = data[2] * m.data[6] + data[5] * m.data[7] + data[8] * m.data[8];
	
	result.data[9] = data[0] * m.data[9] + data[3] * m.data[10] + data[6] * m.data[11] + data[9];
	result.data[10] = data[1] * m.data[9] + data[4] * m.data[10] + data[7] * m.data[11] + data[10];
	result.data[11] = data[2] * m.data[9] + data[5] * m.data[10] + data[8] * m.data[11] + data[11];
	
	return result;
}

Vector3 Matrix3x4::operator*(const Vector3& v) const
{
	Vector3 result;

	result.x_ = data[0] * v.x_ + data[3] * v.y_ + data[6] * v.z_ + data[9];
	result.y_ = data[1] * v.x_ + data[4] * v.y_ + data[7] * v.z_ + data[10];
	result.z_ = data[2] * v.x_ + data[5] * v.y_ + data[8] * v.z_ + data[11];

	return result;
}

Matrix3x4& Matrix3x4::translate(float x, float y, float z)
{
	return translate(Vector3(x, y, z));
}

Matrix3x4& Matrix3x4::translate(const Vector3& v)
{
	data[9] = data[0] * v.x_ + data[3] * v.y_ + data[6] * v.z_ + data[9];
	data[10] = data[1] * v.x_ + data[4] * v.y_ + data[7] * v.z_ + data[10];
	data[11] = data[2] * v.x_ + data[5] * v.y_ + data[8] * v.z_ + data[11];
	return *this;
}

Matrix3x4& Matrix3x4::scale(float value)
{
	return scale(Vector3(value, value, value));
}

Matrix3x4& Matrix3x4::scale(float x, float y, float z)
{
	return scale(Vector3(x, y, z));
}

Matrix3x4& Matrix3x4::scale(const Vector3& v)
{
	data[0] = data[0] * v.x_;
	data[1] = data[1] * v.x_;
	data[2] = data[2] * v.x_;

	data[3] = data[3] * v.y_;
	data[4] = data[4] * v.y_;
	data[5] = data[5] * v.y_;

	data[6] = data[6] * v.z_;
	data[7] = data[7] * v.z_;
	data[8] = data[8] * v.z_;

	return *this;
}

Matrix3x4& Matrix3x4::rotateX(float angle)
{
	Matrix3x4 m = rotationXMatrix(angle);
	(*this) *= m;
	return *this;
}

Matrix3x4& Matrix3x4::rotateY(float angle)
{
	Matrix3x4 m = rotationYMatrix(angle);
	(*this) *= m;
	return *this;
}

Matrix3x4& Matrix3x4::rotateZ(float angle)
{
	Matrix3x4 m = rotationZMatrix(angle);
	(*this) *= m;
	return *this;
}

Matrix3x4& Matrix3x4::rotate(float angle, float x, float y, float z)
{
	return rotate(angle, Vector3(x, y, z));
}

Matrix3x4& Matrix3x4::rotate(float angle, const Vector3& v)
{
	Matrix3x4 m = rotationMatrix(angle, v);
	(*this) *= m;
	return *this;
}

Matrix3x4 Matrix3x4::rotationXMatrix(float angle)
{
	float c = cosf(angle);
	float s = sinf(angle);
	Matrix3x4 result;
	result.data[4] = c;
	result.data[5] = s;
	result.data[7] = -s;
	result.data[8] = c;
	return result;
}

Matrix3x4 Matrix3x4::rotationYMatrix(float angle)
{
	float c = cosf(angle);
	float s = sinf(angle);
	Matrix3x4 result;
	result.data[0] = c;
	result.data[2] = -s;
	result.data[6] = s;
	result.data[8] = c;
	return result;
}

Matrix3x4 Matrix3x4::rotationZMatrix(float angle)
{
	float c = cosf(angle);
	float s = sinf(angle);
	Matrix3x4 result;
	result.data[0] = c;
	result.data[1] = s;
	result.data[3] = -s;
	result.data[4] = c;
	return result;
}

Matrix3x4 Matrix3x4::rotationMatrix(float angle, float x, float y, float z)
{
	return rotationMatrix(angle, Vector3(x, y, z));
}

Matrix3x4 Matrix3x4::rotationMatrix(float angle, const Vector3& v)
{
	float c = cosf(angle);
	float s = sinf(angle);

	Vector3 axis = v.normalized();
	Vector3 temp = axis * (1.0f - c);

	Matrix3x4 result;

	result.data[0] = c + temp.x_ * axis.x_;
	result.data[1] = 0 + temp.x_ * axis.y_ + axis.z_ * s;
	result.data[2] = 0 + temp.x_ * axis.z_ - axis.y_ * s;

	result.data[3] = 0 + temp.y_ * axis.x_ - axis.z_ * s;
	result.data[4] = c + temp.y_ * axis.y_;
	result.data[5] = 0 + temp.y_ * axis.z_ + axis.x_ * s;

	result.data[6] = 0 + temp.z_ * axis.x_ + axis.y_ * s;
	result.data[7] = 0 + temp.z_ * axis.y_ - axis.x_ * s;
	result.data[8] = c + temp.z_ * axis.z_;

	return result;
}

Matrix3x4 Matrix3x4::translationMatrix(float x, float y, float z)
{
	return translationMatrix(Vector3(x, y, z));
}

Matrix3x4 Matrix3x4::translationMatrix(const Vector3& v)
{
	Matrix3x4 m;
	m.data[9] = v.x_;
	m.data[10] = v.y_;
	m.data[11] = v.z_;

	return m;
}

Matrix3x4 Matrix3x4::scaleMatrix(float value)
{
	return scaleMatrix(Vector3(value, value, value));
}

Matrix3x4 Matrix3x4::scaleMatrix(float x, float y, float z)
{
	return scaleMatrix(Vector3(x, y, z));
}

Matrix3x4 Matrix3x4::scaleMatrix(const Vector3& v)
{
	Matrix3x4 m;
	m.data[0] = v.x_;
	m.data[4] = v.y_;
	m.data[8] = v.z_;
	return m;
}