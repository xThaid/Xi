#include "eulerAngles.h"

namespace ximath
{
	EulerAngles::EulerAngles() : pitch(0.0f), yaw(0.0f), roll(0.0f) {}
	EulerAngles::EulerAngles(float pitch, float yaw, float roll) : pitch(pitch), yaw(yaw), roll(roll) {}

	void EulerAngles::add(float pitch, float yaw, float roll)
	{
		this->pitch += pitch;
		this->yaw += yaw;
		this->roll += roll;
	}

	EulerAngles& EulerAngles::operator+=(const EulerAngles& a)
	{
		pitch += a.pitch;
		yaw += a.yaw;
		roll += a.roll;
		return *this;
	}

	EulerAngles& EulerAngles::operator-=(const EulerAngles& a)
	{
		pitch -= a.pitch;
		yaw -= a.yaw;
		roll -= a.roll;
		return *this;
	}

	EulerAngles& EulerAngles::operator*=(const float& value)
	{
		pitch *= value;
		yaw *= value;
		roll *= value;
		return *this;
	}

	EulerAngles EulerAngles::operator+(const EulerAngles& a) const
	{
		return EulerAngles(pitch + a.pitch, yaw + a.yaw, roll + a.roll);
	}

	EulerAngles EulerAngles::operator-(const EulerAngles& a) const
	{
		return EulerAngles(pitch - a.pitch, yaw - a.yaw, roll - a.roll);
	}

	EulerAngles EulerAngles::operator*(const float& value) const
	{
		return EulerAngles(pitch * value, yaw * value, roll * value);
	}

	bool EulerAngles::operator==(const EulerAngles& a) const
	{
		return (pitch == a.pitch && yaw == yaw && roll == a.roll);
	}

	bool EulerAngles::operator!=(const EulerAngles& a) const
	{
		return !(pitch == a.pitch && yaw == yaw && roll == a.roll);
	}
}