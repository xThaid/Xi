#pragma once

//0 3 6 9
//1 4 7 10
//2 5 8 11

class Vector3;

class Matrix3;
class Matrix4;

class Matrix3x4
{
public:
	float data[12];

	Matrix3x4();

	explicit Matrix3x4(const Matrix3& m);
	explicit Matrix3x4(const Matrix4& m);

	inline const float* getPointer() const { return &data[0]; }

	Matrix3x4& operator*=(const Matrix3x4& m);

	Matrix3x4 operator*(const Matrix3x4& m) const;
	Vector3 operator*(const Vector3& v) const;
	
	Matrix3x4& translate(float x, float y, float z);
	Matrix3x4& translate(const Vector3& v);

	Matrix3x4& scale(float value);
	Matrix3x4& scale(float x, float y, float z);
	Matrix3x4& scale(const Vector3& v);

	Matrix3x4& rotateX(float angle);
	Matrix3x4& rotateY(float angle);
	Matrix3x4& rotateZ(float angle);

	Matrix3x4& rotate(float angle, float x, float y, float z);
	Matrix3x4& rotate(float angle, const Vector3& v);

	static Matrix3x4 rotationXMatrix(float angle);
	static Matrix3x4 rotationYMatrix(float angle);
	static Matrix3x4 rotationZMatrix(float angle);

	static Matrix3x4 rotationMatrix(float angle, float x, float y, float z);
	static Matrix3x4 rotationMatrix(float angle, const Vector3& axis);

	static Matrix3x4 translationMatrix(float x, float y, float z);
	static Matrix3x4 translationMatrix(const Vector3& v);

	static Matrix3x4 scaleMatrix(float value);
	static Matrix3x4 scaleMatrix(float x, float y, float z);
	static Matrix3x4 scaleMatrix(const Vector3& v);

private:
	void copy(const Matrix3x4& m);
};