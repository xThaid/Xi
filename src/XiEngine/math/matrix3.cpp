#include "matrix3.h"

#include "../precompiled.h"

#include "../math/vector3.h"
#include "../math/vector4.h"

Matrix3::Matrix3()
{
	data[0] = 1.0f; data[3] = 0.0f; data[6]  = 0.0f;
	data[1] = 0.0f; data[4] = 1.0f; data[7]  = 0.0f;
	data[2] = 0.0f; data[5] = 0.0f; data[8]  = 1.0f;
}

void Matrix3::copy(const Matrix3& m)
{
	data[0] = m.data[0]; data[3] = m.data[3]; data[6] = m.data[6];
	data[1] = m.data[1]; data[4] = m.data[4]; data[7] = m.data[7];
	data[2] = m.data[2]; data[5] = m.data[5]; data[8] = m.data[8];
}

Matrix3& Matrix3::operator*=(const Matrix3& m)
{
	Matrix3 result = (*this) * m;
	copy(result);
	return *this;
}

Matrix3 Matrix3::operator*(const Matrix3& m) const
{
	Matrix3 result;
		
	result.data[0] = data[0] * m.data[0] + data[3] * m.data[1] + data[6] * m.data[2];
	result.data[1] = data[1] * m.data[0] + data[4] * m.data[1] + data[7] * m.data[2];
	result.data[2] = data[2] * m.data[0] + data[5] * m.data[1] + data[8] * m.data[2];

	result.data[3] = data[0] * m.data[3] + data[3] * m.data[4] + data[6] * m.data[5];
	result.data[4] = data[1] * m.data[3] + data[4] * m.data[4] + data[7] * m.data[5];
	result.data[5] = data[2] * m.data[3] + data[5] * m.data[4] + data[8] * m.data[5];

	result.data[6] = data[0] * m.data[6] + data[3] * m.data[7] + data[6] * m.data[8];
	result.data[7] = data[1] * m.data[6] + data[4] * m.data[7] + data[7] * m.data[8];
	result.data[8] = data[2] * m.data[6] + data[5] * m.data[7] + data[8] * m.data[8];

	return result;
}

Vector3 Matrix3::operator*(const Vector3& v) const
{
	Vector3 result;
	
	result.x_ = data[0] * v.x_ + data[3] * v.y_ + data[6] * v.z_;
	result.y_ = data[1] * v.x_ + data[4] * v.y_ + data[7] * v.z_;
	result.z_ = data[2] * v.x_ + data[5] * v.y_ + data[8] * v.z_;
	
	return result;
}

Matrix3& Matrix3::transpose()
{
	float temp;
	temp = data[1]; data[1] = data[3]; data[3] = temp;
	temp = data[2]; data[2] = data[6]; data[6] = temp;
	temp = data[5]; data[5] = data[7]; data[7] = temp;
	return *this;
}

Matrix3 Matrix3::transposed() const
{
	Matrix3 tempMatrix(*this);
	return tempMatrix.transpose();
}

Matrix3& Matrix3::rotateX(float angle)
{
	Matrix3 m = rotationXMatrix(angle);
	(*this) *= m;
	return *this;
}

Matrix3& Matrix3::rotateY(float angle)
{
	Matrix3 m = rotationYMatrix(angle);
	(*this) *= m;
	return *this;
}

Matrix3& Matrix3::rotateZ(float angle)
{
	Matrix3 m = rotationZMatrix(angle);
	(*this) *= m;
	return *this;
}

Matrix3& Matrix3::rotate(float angle, float x, float y, float z)
{
	return rotate(angle, Vector3(x, y, z));
}

Matrix3& Matrix3::rotate(float angle, const Vector3& v)
{
	Matrix3 m = rotationMatrix(angle, v);
	(*this) *= m;
	return *this;
}

Matrix3 Matrix3::rotationXMatrix(float angle)
{
	float c = cosf(angle);
	float s = sinf(angle);
	Matrix3 result;
	result.data[4] = c;
	result.data[5] = s;
	result.data[7] = -s;
	result.data[8] = c;
	return result;
}

Matrix3 Matrix3::rotationYMatrix(float angle)
{
	float c = cosf(angle);
	float s = sinf(angle);
	Matrix3 result;
	result.data[0] = c;
	result.data[2] = -s;
	result.data[6] = s;
	result.data[8] = c;
	return result;
}

Matrix3 Matrix3::rotationZMatrix(float angle)
{
	float c = cosf(angle);
	float s = sinf(angle);
	Matrix3 result;
	result.data[0] = c;
	result.data[1] = s;
	result.data[3] = -s;
	result.data[4] = c;
	return result;
}

Matrix3 Matrix3::rotationMatrix(float angle, float x, float y, float z)
{
	return rotationMatrix(angle, Vector3(x, y, z));
}

Matrix3 Matrix3::rotationMatrix(float angle, const Vector3& v)
{
	float c = cosf(angle);
	float s = sinf(angle);

	Vector3 axis = v.normalized();
	Vector3 temp = axis * (1.0f - c);

	Matrix3 result;

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