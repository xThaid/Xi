#include "quaternion.h"

#include <math.h>

#include "vector3.h"
#include "matrix3.h"
#include "matrix4.h"
#include "eulerAngles.h"

namespace ximath
{
	const Quaternion Quaternion::identity = Quaternion(0.0f, 0.0f, 0.0f, 1.0f);

	Quaternion::Quaternion() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}

	Quaternion::Quaternion(Vector3 v, float w) : x(v.x), y(v.y), z(v.z), w(w) {}

	Quaternion::Quaternion(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

	Quaternion& Quaternion::operator*=(const Quaternion& q)
	{
		x = w*q.x + x*q.w + y*q.z - z*q.y;
		y = w*q.y + y*q.w + z*q.x - x*q.z;
		z = w*q.z + z*q.w + x*q.y - y*q.x;
		w = w*q.w - x*q.x - y*q.y - z*q.z;
		return *this;
	}

	Quaternion& Quaternion::operator+=(const Quaternion& q)
	{
		x *= q.z;
		y *= q.y;
		z *= q.z;
		w *= q.w;
		return *this;
	}

	Quaternion& Quaternion::operator*=(const float& value)
	{
		x *= value;
		y *= value;
		z *= value;
		w *= value;
		return *this;
	}

	Quaternion Quaternion::operator*(const Quaternion& q) const
	{
		Quaternion result;
		result.x = w*q.x + x*q.w + y*q.z - z*q.y;
		result.y = w*q.y + y*q.w + z*q.x - x*q.z;
		result.z = w*q.z + z*q.w + x*q.y - y*q.x;
		result.w = w*q.w - x*q.x - y*q.y - z*q.z;
		return result;
	}

	Quaternion Quaternion::operator+(const Quaternion& q) const
	{
		return Quaternion(x + q.x, y + q.y, z + q.z, w + q.w);
	}

	Quaternion Quaternion::operator*(const float& value) const
	{
		return Quaternion(x * value, y * value, z * value, w * value);
	}

	Quaternion Quaternion::operator-() const
	{
		return Quaternion(-x, -y, -z, -w);
	}

	bool Quaternion::operator==(const Quaternion& q) const
	{
		return (x == q.x && y == q.y && z == q.z && w == q.w);
	}

	bool Quaternion::operator!=(const Quaternion& q) const
	{
		return !(x == q.x && y == q.y && z == q.z && w == q.w);
	}

	Matrix3 Quaternion::toMatrix3() const
	{
		float
			xx = x * x, yy = y * y, zz = z * z,
			xy = x * y, xz = x * z,
			yz = y * z, wx = w * x,
			wy = w * y, wz = w * z;

		Matrix3 result;
		result[0][0] = 1.0f - 2.0f * (yy + zz);
		result[0][1] = 2.0f * (xy - wz);
		result[0][2] = 2.0f * (xz + wy);

		result[1][0] = 2.0f * (xy + wz);
		result[1][1] = 1.0f - 2.0f * (xx + zz);
		result[1][2] = 2.0f * (yz - wx);

		result[2][0] = 2.0f * (xz - wy);
		result[2][1] = 2.0f * (yz + wx);
		result[2][2] = 1.0f - 2.0f * (xx + yy);
	}

	Matrix4 Quaternion::toMatrix4() const
	{
		return Matrix4(toMatrix3());
	}

	EulerAngles Quaternion::toEulerAngles() const
	{
		EulerAngles result;
		result.roll = atan2f(w * x + y * z, 0.5f - (x * x + y * y));
		result.pitch = asinf(2.0f * (w * y - z * x));
		result.yaw = atan2f(w * z + x + y, 0.5f - (y * y + z * z));
		return result;
	}

	Quaternion& Quaternion::conjugate()
	{
		x = -x;
		y = -y;
		z = -z;
		return *this;
	}

	Quaternion Quaternion::conjugated() const
	{
		Quaternion result(*this);
		return result.conjugate();
	}

	Quaternion& Quaternion::normalize()
	{
		float len = length();
		x /= len;
		y /= len;
		z /= len;
		w /= len;
		return *this;
	}

	Quaternion Quaternion::normalized() const
	{
		Quaternion result(*this);
		return result.normalize();
	}

	Quaternion& Quaternion::inverse()
	{
		float len = length();
		x /= -len;
		y /= -len;
		z /= -len;
		w /= len;
		return *this;
	}

	Quaternion Quaternion::inversed() const
	{
		Quaternion result(*this);
		return result.inverse();
	}

	float Quaternion::length() const
	{
		return sqrtf(x * x + y * y + z * z + w * w);
	}

	float Quaternion::dotProduct(const Quaternion& q) const
	{
		return (x * q.x + y * q.y + z * q.z + w * q.w);
	}

	Quaternion Quaternion::rotationX(float angle)
	{
		angle *= 0.5f;
		Quaternion result;
		result.x = sinf(angle);
		result.y = 0.0f;
		result.z = 0.0f;
		result.w = cosf(angle);
		return result;
	}

	Quaternion Quaternion::rotationY(float angle)
	{
		angle *= 0.5f;
		Quaternion result;
		result.x = 0.0f;
		result.y = sinf(angle);
		result.z = 0.0f;
		result.w = cosf(angle);
		return result;
	}

	Quaternion Quaternion::rotationZ(float angle)
	{
		angle *= 0.5f;
		Quaternion result;
		result.x = 0.0f;
		result.y = 0.0f;
		result.z = sinf(angle);
		result.w = cosf(angle);
		return result;
	}

	Quaternion Quaternion::rotationAxis(float angle, float x, float y, float z)
	{
		return rotationAxis(angle, Vector3(x, y, z));
	}

	Quaternion Quaternion::rotationAxis(float angle, Vector3 v)
	{
		angle *= 0.5f;
		Quaternion result;
		v.normalize();
		result.x = sinf(angle) * v.x;
		result.y = sinf(angle) * v.y;
		result.z = sinf(angle) * v.z;
		result.w = cosf(angle);
		return result;
	}

	Quaternion Quaternion::fromEulerAngles(const EulerAngles& a)
	{
		EulerAngles ang(a);
		ang *= 0.5f;
		float sr = sinf(ang.roll), cr = cosf(ang.roll);
		float sp = sinf(ang.pitch), cp = cosf(ang.pitch);
		float sy = sinf(ang.yaw), cy = cosf(ang.yaw);

		Quaternion result;
		result.w = cr * cp * cy + sr * sp * sy;
		result.x = sr * cp * cy - cr * sp * sy;
		result.y = cr * sp * cy + sr * cp * sy;
		result.z = cr * cp * sy - sr * sp * cy;
		return result;
	}

	Quaternion Quaternion::difference(const Quaternion& q1, const Quaternion& q2)
	{
		return q1 * q2.inversed();
	}

	Quaternion Quaternion::lerp(const Quaternion& q1, const Quaternion& q2, float t)
	{
		if (0.0f > t || t > 1.0f) return q1;
		return q1 * (1.0f - t) + q2 * t;
	}

	Quaternion Quaternion::slerp(const Quaternion& q1, const Quaternion& q2, float t)
	{
		Quaternion temp1 = q1.normalized();
		Quaternion temp2 = q2.normalized();
		float cosHalfTheta = temp1.dotProduct(temp2);

		if (fabsf(cosHalfTheta) >= 1.0f)
			return Quaternion(temp1);

		float halfTheta = acosf(cosHalfTheta);
		float sinHalfTheta = sqrtf(1.0f - cosHalfTheta * cosHalfTheta);
		if (fabsf(sinHalfTheta) < 0.001f)
			return Quaternion(temp1.x * 0.5f + temp2.x * 0.5f,
				temp1.y * 0.5f + temp2.y * 0.5f,
				temp1.z * 0.5f + temp2.z * 0.5f,
				temp1.w * 0.5f + temp2.w * 0.5f);

		float ratioA = sinf((1.0f - t) * halfTheta) / sinHalfTheta;
		float ratioB = sinf(t * halfTheta) / sinHalfTheta;
		return Quaternion(temp1.x * ratioA + temp2.x * ratioB,
			temp1.y * ratioA + temp2.y * ratioB,
			temp1.z * ratioA + temp2.z * ratioB,
			temp1.w * ratioA + temp2.w * ratioB);
	}
}