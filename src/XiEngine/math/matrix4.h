#pragma once


class Vector3;
class Vector4;

class Matrix4
{
public:
	float data[16];
		
	Matrix4();

	inline const float* getPointer() { return &data[0]; }

	Matrix4& operator*=(const Matrix4& m);

	Matrix4 operator*(const Matrix4& m) const;
	Vector3 operator*(const Vector3& v) const;
	Vector4 operator*(const Vector4& v) const;

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

	static Matrix4 rotationXMatrix(float angle);
	static Matrix4 rotationYMatrix(float angle);
	static Matrix4 rotationZMatrix(float angle);

	static Matrix4 rotationMatrix(float angle, float x, float y, float z);
	static Matrix4 rotationMatrix(float angle, Vector3 axis);

	static Matrix4 translationMatrix(float x, float y, float z);
	static Matrix4 translationMatrix(Vector3 v);

	static Matrix4 scaleMatrix(float x, float y, float z);
	static Matrix4 scaleMatrix(Vector3 v);

	static Matrix4 perspective(float fovy, float aspect, float znear, float zfar);
	static Matrix4 ortho(float left, float right, float bottom, float top, float znear, float zfar);
	static Matrix4 lookAt(const Vector3& eye, const Vector3& target, const Vector3& up);

private:
	void copy(const Matrix4& m);
};