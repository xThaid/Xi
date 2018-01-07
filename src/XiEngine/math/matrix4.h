#pragma once

class Vector3;
class Vector4;

class Matrix3;
class Matrix3x4;

//0 4 8  12
//1 5 9  13
//2 6 10 14
//3 7 11 15

class Matrix4
{
public:
	float data[16];
		
	Matrix4();

	explicit Matrix4(const Matrix3& m);
	explicit Matrix4(const Matrix3x4& m);

	inline const float* getPointer() { return &data[0]; }

	Matrix4& operator*=(const Matrix4& m);

	Matrix4 operator*(const Matrix4& m) const;
	Vector3 operator*(const Vector3& v) const;
	Vector4 operator*(const Vector4& v) const;

	Matrix4& transpose();
	Matrix4 transposed() const;

	static Matrix4 orthoMatrix(float left, float right, float bottom, float top);
	static Matrix4 orthoMatrix(float left, float right, float bottom, float top, float znear, float zfar);
	static Matrix4 lookAtMatrix(const Vector3& eye, const Vector3& target, const Vector3& up);

private:
	void copy(const Matrix4& m);
};