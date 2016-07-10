#include "matrix4.h"

#include <stdexcept>
#include <math.h>

#include "vector3.h"
#include "matrix3.h"
#include "quaternion.h"

namespace ximath
{
	const Matrix4 Matrix4::identity = Matrix4(
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
	);

	Matrix4::Matrix4()
	{
		data[0] = Vector4();
		data[1] = Vector4();
		data[2] = Vector4();
		data[3] = Vector4();
	}

	Matrix4::Matrix4(float value)
	{
		data[0] = Vector4(value, 0.0f, 0.0f, 0.0f);
		data[1] = Vector4(0.0f, value, 0.0f, 0.0f);
		data[2] = Vector4(0.0f, 0.0f, value, 0.0f);
		data[3] = Vector4(0.0f, 0.0f, 0.0f, value);
	}

	Matrix4::Matrix4(const Vector4 v1, const Vector4 v2, const Vector4 v3, const Vector4 v4)
	{
		data[0] = v1;
		data[1] = v2;
		data[2] = v3;
		data[3] = v4;
	}

	Matrix4::Matrix4(const Matrix3& m)
	{
		data[0] = Vector4(m[0][0], m[0][1], m[0][2], 0.0f);
		data[1] = Vector4(m[1][0], m[1][1], m[1][2], 0.0f);
		data[2] = Vector4(m[2][0], m[2][1], m[2][2], 0.0f);
		data[3] = Vector4(0.0f, 0.0f, 0.0f, 1.0f);
	}

	Matrix4::Matrix4(float data00, float data01, float data02,
		float data10, float data11, float data12,
		float data20, float data21, float data22)
	{
		data[0] = Vector4(data00, data01, data02, 0.0f);
		data[1] = Vector4(data10, data11, data12, 0.0f);
		data[2] = Vector4(data20, data21, data22, 0.0f);
		data[3] = Vector4(0.0f, 0.0f, 0.0f, 0.0f);
	}

	Matrix4::Matrix4(float data00, float data01, float data02, float data03,
		float data10, float data11, float data12, float data13,
		float data20, float data21, float data22, float data23,
		float data30, float data31, float data32, float data33)
	{
		data[0] = Vector4(data00, data01, data02, data03);
		data[1] = Vector4(data10, data11, data12, data13);
		data[2] = Vector4(data20, data21, data22, data23);
		data[2] = Vector4(data30, data31, data32, data33);
	}

	Matrix4& Matrix4::operator+=(const Matrix4& m)
	{
		data[0] += m.data[0];
		data[1] += m.data[1];
		data[2] += m.data[2];
		data[3] += m.data[3];
		return *this;
	}

	Matrix4& Matrix4::operator-=(const Matrix4& m)
	{
		data[0] -= m.data[0];
		data[1] -= m.data[1];
		data[2] -= m.data[2];
		data[3] -= m.data[3];
		return *this;
	}

	Matrix4& Matrix4::operator*=(const Matrix4& m)
	{
		const Matrix4 copyOfThis(*this);
		multiplicationHelper(copyOfThis, m, this);
		return *this;
	}

	Matrix4& Matrix4::operator*=(const Matrix3& m)
	{
		const Matrix4 copyOfThis(*this);
		multiplicationHelper(copyOfThis, m, this);
		return *this;
	}

	Matrix4& Matrix4::operator*=(const float& value)
	{
		data[0] *= value;
		data[1] *= value;
		data[2] *= value;
		data[3] *= value;
		return *this;
	}

	Matrix4& Matrix4::operator/=(const float& value)
	{
		data[0] /= value;
		data[1] /= value;
		data[2] /= value;
		data[3] /= value;
		return *this;
	}

	Matrix4 Matrix4::operator+(const Matrix4& m) const
	{
		return Matrix4(data[0] + m.data[0], data[1] + m.data[1], data[2] + m.data[2], data[3] + m.data[3]);
	}

	Matrix4 Matrix4::operator-(const Matrix4& m) const
	{
		return Matrix4(data[0] - m.data[0], data[1] - m.data[1], data[2] - m.data[2], data[3] - m.data[3]);
	}

	Matrix4 Matrix4::operator*(const Matrix4& m) const
	{
		Matrix4 result;
		multiplicationHelper(*this, m, &result);
		return result;
	}

	Matrix4 Matrix4::operator*(const Matrix3& m) const
	{
		Matrix4 result;
		multiplicationHelper(*this, m, &result);
		return result;
	}

	Matrix4 Matrix4::operator*(const float& value) const
	{
		return Matrix4(data[0] * value, data[1] * value, data[2] * value, data[3] * value);
	}

	Matrix4 Matrix4::operator/(const float& value) const
	{
		return Matrix4(data[0] / value, data[1] / value, data[2] / value, data[3] / value);
	}

	Matrix4 Matrix4::operator-() const
	{
		return Matrix4(-data[0], -data[1], -data[2], -data[3]);
	}

	Vector4 Matrix4::operator*(const Vector4& v) const
	{
		Vector4 result;
		for (int i = 0; i < 4; i++)
			result[i] = dot(v, data[i]);

		return result;
	}

	Vector4& Matrix4::operator[](const unsigned int i)
	{
		if (i < 4)
			return data[i];

		throw std::out_of_range("out of range // TODO");
	}

	const Vector4& Matrix4::operator[](const unsigned int i) const
	{
		if (i < 4)
			return data[i];

		throw std::out_of_range("out of range // TODO");
	}

	Vector4 Matrix4::getColumn(const unsigned int i) const
	{
		if (i < 4)
			return Vector4(data[0][i], data[1][i], data[2][i], data[3][i]);

		throw std::out_of_range("out of range // TODO");
	}

	bool Matrix4::operator==(const Matrix4& m) const
	{
		return (data[0] == m.data[0] && data[1] == m.data[1] && data[2] == m.data[2] && data[3] == m.data[3]);
	}

	bool Matrix4::operator!=(const Matrix4& m) const
	{
		return !(data[0] == m.data[0] && data[1] == m.data[1] && data[2] == m.data[2] && data[3] == m.data[3]);
	}

	Matrix4& Matrix4::transpose()
	{
		float temp;
		temp = data[0][1]; data[0][1] = data[1][0]; data[1][0] = temp;
		temp = data[0][2]; data[0][2] = data[2][0]; data[2][0] = temp;
		temp = data[0][3]; data[0][3] = data[3][0]; data[3][0] = temp;
		temp = data[1][2]; data[1][2] = data[2][1]; data[2][1] = temp;
		temp = data[1][3]; data[1][3] = data[3][1]; data[3][1] = temp;
		temp = data[2][3]; data[2][3] = data[3][2]; data[3][2] = temp;
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
		Vector4 temp(v, 1.0f);
		data[0][3] = data[0].dotProduct(temp);
		data[1][3] = data[1].dotProduct(temp);
		data[2][3] = data[2].dotProduct(temp);
		data[3][3] = data[3].dotProduct(temp);
		return *this;
	}

	Matrix4& Matrix4::scale(float x, float y, float z)
	{
		return scale(Vector3(x, y, z));
	}

	Matrix4& Matrix4::scale(const Vector3& v)
	{
		Vector4 temp(v, 1.0f);
		data[0] = data[0] * temp;
		data[1] = data[1] * temp;
		data[2] = data[2] * temp;
		data[3] = data[3] * temp;
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
		return (*this) *= m;
	}

	Matrix4& Matrix4::rotate(const Matrix3& m)
	{
		(*this) *= m;
		return *this;
	}

	Matrix4& Matrix4::rotate(const EulerAngles& angles)
	{

		(*this) *= Quaternion::fromEulerAngles(angles).toMatrix4();
		return *this;
	}

	Matrix4& Matrix4::rotate(const Quaternion& quat)
	{
		Matrix4 m = quat.toMatrix4();
		(*this) *= m;
		return *this;
	}

	Matrix4 Matrix4::rotationXMatrix(float angle)
	{
		float c = cosf(angle);
		float s = sinf(angle);
		return Matrix4(1.0f, 0.0f, 0.0f, 0.0f, c, -s, 0.0f, s, c);
	}

	Matrix4 Matrix4::rotationYMatrix(float angle)
	{
		float c = cosf(angle);
		float s = sinf(angle);
		return Matrix4(c, 0.0f, s, 0.0f, 1, 0.0f, -s, 0, c);
	}

	Matrix4 Matrix4::rotationZMatrix(float angle)
	{
		float c = cosf(angle);
		float s = sinf(angle);
		return Matrix4(c, -s, 0.0f, s, c, 0.0f, 0.0f, 0.0f, 1.0f);
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

		result[0][0] = c + temp[0] * axis[0];
		result[0][1] = 0 + temp[0] * axis[1] - axis[2] * s;
		result[0][2] = 0 + temp[0] * axis[2] + axis[1] * s;

		result[1][0] = 0 + temp[1] * axis[0] + axis[2] * s;
		result[1][1] = c + temp[1] * axis[1];
		result[1][2] = 0 + temp[1] * axis[2] - axis[0] * s;

		result[2][0] = 0 + temp[2] * axis[0] - axis[1] * s;
		result[2][1] = 0 + temp[2] * axis[1] + axis[0] * s;
		result[2][2] = c + temp[2] * axis[2];

		return result;
	}

	Matrix4 Matrix4::translationMatrix(float x, float y, float z)
	{
		return translationMatrix(Vector3(x, y, z));
	}

	Matrix4 Matrix4::translationMatrix(Vector3 v)
	{
		Matrix4 m(identity);
		m[0][3] = v.x;
		m[1][3] = v.y;
		m[2][3] = v.z;

		return m;
	}

	Matrix4 Matrix4::scaleMatrix(float x, float y, float z)
	{
		return scaleMatrix(Vector3(x, y, z));
	}

	Matrix4 Matrix4::scaleMatrix(Vector3 v)
	{
		Matrix4 m;
		m[0][0] = v.x;
		m[1][1] = v.y;
		m[2][2] = v.z;
		m[3][3] = 1.0f;

		return m;
	}

	void Matrix4::multiplicationHelper(const Matrix4& m1, const	Matrix4& m2, Matrix4* m_out)
	{
		Matrix4& out = *m_out;

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
				out[i][j] = m2.getColumn(j).dotProduct(m1[i]);
		}
	}

	void Matrix4::multiplicationHelper(const Matrix4& m1, const	Matrix3& m2, Matrix4* m_out)
	{
		Matrix4& out = *m_out;

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 3; j++)
				out[i][j] = Vector4(m2.getColumn(j), 0.0f).dotProduct(m1[i]);
			out[i][3] = m1[i][3];
		}
	}

	Matrix4 operator*(const float& value, const Matrix4& m)
	{
		return m * value;
	}

	Matrix4 perspective(float fovy, float aspect, float znear, float zfar)
	{
		Matrix4 m;
		const float tg = tanf(fovy / 2.0f);
		const float dist = znear - zfar;

		m[0][0] = 1.0f / (tg * aspect);
		m[1][1] = 1.0f / tg;
		m[2][2] = (-znear - zfar) / dist;
		m[2][3] = 2.0f * zfar * znear / dist;
		m[3][2] = 1.0f;

		return m;
	}

	Matrix4 ortho(float left, float right, float bottom, float top, float znear, float zfar)
	{
		Matrix4 m;
		m[0][0] = 2.0f / (right - left);
		m[0][3] = -((right + left) / (right - left));
		m[1][1] = 2.0f / (top - bottom);
		m[1][3] = -((top + bottom) / (top - bottom));
		m[2][2] = -2.0f / (zfar - znear);
		m[2][3] = -((zfar + znear) / (zfar - znear));
		m[3][3] = 1.0f;

		return m;
	}

	Matrix4 lookAt(const Vector3& eye, const Vector3& at, const Vector3& up)
	{
		Vector3 zAxis = (eye - at).normalized();
		Vector3 xAxis = up.crossProduct(zAxis).normalized();
		Vector3 yAxis = zAxis.crossProduct(xAxis);

		return Matrix4(xAxis.x, yAxis.x, zAxis.x, 0.0f,
			xAxis.y, yAxis.y, zAxis.y, 0.0f,
			xAxis.z, yAxis.z, zAxis.z, 0.0f,
			-xAxis.dotProduct(eye), -yAxis.dotProduct(eye), -zAxis.dotProduct(eye), 1.0f);
	}
}