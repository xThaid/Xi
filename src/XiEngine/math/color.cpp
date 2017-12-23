#include "color.h"

#include "../math/mathDefs.h"

Color::Color() :
	r(1.0f),
	g(1.0f),
	b(1.0f),
	a(1.0f)
{
}

Color::Color(float r, float g, float b) :
	r(r),
	g(g),
	b(b),
	a(1.0f)
{
}

Color::Color(float r, float g, float b, float a) :
	r(r),
	g(g),
	b(b),
	a(a)
{
}

unsigned int Color::toUInt() const
{
	unsigned int tempR = (unsigned int) clamp(r * 255.0f, 0.0f, 255.0f);
	unsigned int tempG = (unsigned int) clamp(g * 255.0f, 0.0f, 255.0f);
	unsigned int tempB = (unsigned int) clamp(b * 255.0f, 0.0f, 255.0f);
	unsigned int tempA = (unsigned int) clamp(a * 255.0f, 0.0f, 255.0f);
	return (tempA << 24) | (tempB << 16) | (tempG << 8) | tempR;
}

const Color Color::WHITE(1.0f, 1.0f, 1.0f);
const Color Color::GRAY(0.5f, 0.5f, 0.5f);
const Color Color::BLACK(0.0f, 0.0f, 0.0f);
const Color Color::RED(1.0f, 0.0f, 0.0f);
const Color Color::GREEN(0.0f, 1.0f, 0.0f);
const Color Color::BLUE(0.0f, 0.0f, 1.0f);
const Color Color::CYAN(0.0f, 1.0f, 1.0f);
const Color Color::MAGENTA(1.0f, 0.0f, 1.0f);
const Color Color::YELLOW(1.0f, 1.0f, 0.0f);
const Color Color::PINK(1.0f, 0.78f, 0.78f);
const Color Color::ORANGE(1.0f, 0.5f, 0.0f);
