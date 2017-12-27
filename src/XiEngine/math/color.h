#pragma once

class Color
{
public:
	float r;
	float g;
	float b;
	float a;

	Color();
	explicit Color(float r, float g, float b);
	explicit Color(float r, float g, float b, float a);
	
	unsigned int toUInt() const;

	inline float* getPointer() { return &r; }

	static const Color WHITE;
	static const Color GRAY;
	static const Color BLACK;
	static const Color RED;
	static const Color GREEN;
	static const Color BLUE;
	static const Color CYAN;
	static const Color MAGENTA;
	static const Color YELLOW;
	static const Color PINK;
	static const Color ORANGE;
};