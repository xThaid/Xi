#pragma once

class Vector3;
class Vector4;

//0 3 6 
//1 4 7
//2 5 8

class Matrix3
{
public:
	float data[9];
		
	Matrix3();

	inline const float* getPointer() { return &data[0]; }

	Matrix3& operator*=(const Matrix3& m);

	Matrix3 operator*(const Matrix3& m) const;
	Vector3 operator*(const Vector3& v) const;

	Matrix3& transpose();
	Matrix3 transposed() const;

	Matrix3& rotateX(float angle);
	Matrix3& rotateY(float angle);
	Matrix3& rotateZ(float angle);

	Matrix3& rotate(float angle, float x, float y, float z);
	Matrix3& rotate(float angle, const Vector3& v);

	static Matrix3 rotationXMatrix(float angle);
	static Matrix3 rotationYMatrix(float angle);
	static Matrix3 rotationZMatrix(float angle);

	static Matrix3 rotationMatrix(float angle, float x, float y, float z);
	static Matrix3 rotationMatrix(float angle, const Vector3& axis);

private:
	void copy(const Matrix3& m);
};