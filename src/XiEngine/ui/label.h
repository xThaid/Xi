#pragma once

#include "../precompiled.h"

#include "../math/ximath.h"

class Label
{
public:
	Label(const std::string& text, const Vector2& position, float scale = 1.0f, Color color = Color::WHITE);
	~Label();

	void setText(const std::string& text);
	void setPosition(float x, float y);
	void setPosition(const Vector2& position);
	void setScale(float scale);
	void setColor(const Color& color);

	inline std::string& getText() { return text_; }
	inline Vector2 getPosition() { return position_; }
	inline float getScale() { return scale_; }
	inline Color getColor() { return color_; }

private:
	std::string text_;
	Vector2 position_;
	float scale_;
	Color color_;
};