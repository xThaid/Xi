#pragma once

namespace ximath
{
	class EulerAngles
	{
	public:
		float pitch, yaw, roll;

		EulerAngles();
		explicit EulerAngles(float pitch, float yaw, float roll);

		void add(float pitch, float yaw, float roll);

		EulerAngles& operator+=(const EulerAngles& a);
		EulerAngles& operator-=(const EulerAngles& a);
		EulerAngles& operator*=(const float& value);

		EulerAngles operator+(const EulerAngles& a) const;
		EulerAngles operator-(const EulerAngles& a) const;
		EulerAngles operator*(const float& value) const;

		bool operator==(const EulerAngles& a) const;
		bool operator!=(const EulerAngles& a) const;

	};
}