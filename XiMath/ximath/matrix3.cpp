#include "matrix3.h"

#include <stdexcept>

namespace ximath
{
	const Matrix3 Matrix3::identity = Matrix3(
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f
	);

	Matrix3::Matrix3()
	{
		data[0] = Vector3();
		data[1] = Vector3();
		data[2] = Vector3();
	}

	Matrix3::Matrix3(float value)
	{
		data[0] = Vector3(value, 0.0f, 0.0f);
		data[1] = Vector3(0.0f, value, 0.0f);
		data[2] = Vector3(0.0f, 0.0f, value);
	}

	Matrix3::Matrix3(const Vector3 v1, const Vector3 v2, const Vector3 v3) 
	{
		data[0] = v1;
		data[1] = v2;
		data[2] = v3;
	}

	Matrix3::Matrix3(float data00, float data01, float data02,
		float data10, float data11, float data12,
		float data20, float data21, float data22)
	{
		data[0] = Vector3(data00, data01, data02);
		data[1] = Vector3(data10, data11, data12);
		data[2] = Vector3(data20, data21, data22);
	}

	Matrix3& Matrix3::operator+=(const Matrix3& m)
	{
		data[0] += m.data[0];
		data[1] += m.data[1];
		data[2] += m.data[2];
		return *this;
	}

	Matrix3& Matrix3::operator-=(const Matrix3& m)
	{
		data[0] -= m.data[0];
		data[1] -= m.data[1];
		data[2] -= m.data[2];
		return *this;
	}

	Matrix3& Matrix3::operator*=(const Matrix3& m)
	{
		const Matrix3 copyOfThis(*this);
		multiplicationHelper(copyOfThis, m, this);
		return *this;
	}

	Matrix3& Matrix3::operator*=(const float& value)
	{
		data[0] *= value;
		data[1] *= value;
		data[2] *= value;
		return *this;
	}

	Matrix3& Matrix3::operator/=(const float& value)
	{
		data[0] /= value;
		data[1] /= value;
		data[2] /= value;
		return *this;
	}

	Matrix3 Matrix3::operator+(const Matrix3& m) const
	{
		return Matrix3(data[0] + m.data[0], data[1] + m.data[1], data[2] + m.data[2]);
	}

	Matrix3 Matrix3::operator-(const Matrix3& m) const
	{
		return Matrix3(data[0] - m.data[0], data[1] - m.data[1], data[2] - m.data[2]);
	}

	Matrix3 Matrix3::operator*(const Matrix3& m) const
	{
		Matrix3 result;
		multiplicationHelper(*this, m, &result);
		return result;
	}

	Matrix3 Matrix3::operator*(const float& value) const
	{
		return Matrix3(data[0] * value, data[1] * value, data[2] * value);
	}

	Matrix3 Matrix3::operator/(const float& value) const
	{
		return Matrix3(data[0] / value, data[1] / value, data[2] / value);
	}

	Matrix3 Matrix3::operator-() const
	{
		return Matrix3(-data[0], -data[1], -data[2]);
	}

	Vector3 Matrix3::operator*(const Vector3& v) const
	{
		Vector3 result;
		for (int i = 0; i < 3; i++)
			result[i] = data[i].dotProduct(v);
		return result;
	}

	Vector3& Matrix3::operator[](const unsigned int i)
	{
		if (i < 3)
			return data[i];

		throw std::out_of_range("out of range // TODO");
	}

	const Vector3& Matrix3::operator[](const unsigned int i) const
	{
		if (i < 3)
			return data[i];

		throw std::out_of_range("out of range // TODO");
	}

	Vector3 Matrix3::getColumn(const unsigned int i) const
	{
		if(i < 3)
			return Vector3(data[0][i], data[1][i], data[2][i]);

		throw std::out_of_range("out of range // TODO");
	}

	bool Matrix3::operator==(const Matrix3& m) const
	{
		return (data[0] == m.data[0] && data[1] == m.data[1] && data[2] == m.data[2]);
	}

	bool Matrix3::operator!=(const Matrix3& m) const
	{
		return !(data[0] == m.data[0] && data[1] == m.data[1] && data[2] == m.data[2]);
	}

	float Matrix3::determinant() const
	{
		float p = data[0][0] * data[1][1] * data[2][2] + data[0][1] * data[1][2] * data[2][0] + data[0][2] * data[1][0] * data[2][1];
		float n = data[0][2] * data[1][1] * data[2][0] + data[0][0] * data[1][2] * data[2][1] + data[0][1] * data[1][0] * data[2][2];
		return p - n;
	}

	Matrix3& Matrix3::invert()
	{
		Matrix3 copy = *this;
		float det = copy.determinant();

		if (det != 0.0f)
		{
			data[0][0] = ((copy.data[1][1] * copy.data[2][2]) - (copy.data[1][2] * copy.data[2][1])) / det;
			data[1][0] = ((copy.data[2][0] * copy.data[1][2]) - (copy.data[1][0] * copy.data[2][2])) / det;
			data[2][0] = ((copy.data[1][0] * copy.data[2][1]) - (copy.data[2][0] * copy.data[1][1])) / det;
			data[0][1] = ((copy.data[0][2] * copy.data[2][1]) - (copy.data[0][1] * copy.data[2][2])) / det;
			data[1][1] = ((copy.data[0][0] * copy.data[2][2]) - (copy.data[2][0] * copy.data[0][2])) / det;
			data[2][1] = ((copy.data[2][0] * copy.data[0][1]) - (copy.data[0][0] * copy.data[2][1])) / det;
			data[0][2] = ((copy.data[0][1] * copy.data[1][2]) - (copy.data[0][2] * copy.data[1][1])) / det;
			data[1][2] = ((copy.data[1][0] * copy.data[0][2]) - (copy.data[0][0] * copy.data[1][2])) / det;
			data[2][2] = ((copy.data[0][0] * copy.data[1][1]) - (copy.data[1][0] * copy.data[0][1])) / det;
		}

		return *this;
	}

	Matrix3 Matrix3::inverted() const
	{
		Matrix3 tempMatrix(*this);
		return tempMatrix.invert();
	}

	Matrix3& Matrix3::transpose()
	{
		float temp;
		temp = data[0][1]; data[0][1] = data[1][0]; data[1][0] = temp;
		temp = data[0][2]; data[0][2] = data[2][0]; data[2][0] = temp;
		temp = data[1][2]; data[1][2] = data[2][1]; data[2][1] = temp;
		return *this;
	}

	Matrix3 Matrix3::transposed() const
	{
		Matrix3 tempMatrix(*this);
		return tempMatrix.transpose();
	}

	Matrix3 Matrix3::rotationXMatrix(float angle)
	{
		float c = cosf(angle);
		float s = sinf(angle);
		return Matrix3(1.0f, 0.0f, 0.0f, 0.0f, c, -s, 0.0f, s, c);
	}

	Matrix3 Matrix3::rotationYMatrix(float angle)
	{
		float c = cosf(angle);
		float s = sinf(angle);
		return Matrix3(c, 0.0f, s, 0.0f, 1, 0.0f, -s, 0, c);
	}

	Matrix3 Matrix3::rotationZMatrix(float angle)
	{
		float c = cosf(angle);
		float s = sinf(angle);
		return Matrix3(c, -s, 0.0f, s, c, 0.0f, 0.0f, 0.0f, 1.0f);
	}

	Matrix3 Matrix3::rotationMatrix(float angle, float x, float y, float z)
	{
		return rotationMatrix(angle, Vector3(x, y, z));
	}

	Matrix3 Matrix3::rotationMatrix(float angle, Vector3 v)
	{
		float c = cosf(angle);
		float s = sinf(angle);

		Vector3 axis = v.normalized();
		Vector3 temp = axis * (1.0f - c);

		Matrix3 result;

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

	void Matrix3::multiplicationHelper(const Matrix3& m1, const	Matrix3& m2, Matrix3* m_out)
	{
		Matrix3& out = *m_out;

		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
				out[i][j] = m1[i].dotProduct(m2.getColumn(j));
		}
	}

	Matrix3 operator*(const float& value, const Matrix3& m)
	{
		return m * value;
	}

}