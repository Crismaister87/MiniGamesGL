#pragma once
#include <algorithm>

class RGBColor
{
private:
	float Red;
	float Green;
	float Blue;

	inline float clamp(float c) { return c >= 0.0f ? (c <= 1.0f ? c : 1.0f) : 0.0f; };

public:
	RGBColor() { Red = 0.0f; Green = 0.0f; Blue = 0.0f; }
	RGBColor(float r, float g, float b) { Red = clamp(r); Green = clamp(g); Blue = clamp(b); };

	inline float r() const { return Red; };
	inline float g() const { return Green; };
	inline float b() const { return Blue; };

	inline void setR(float r) { Red = clamp(r); };
	inline void setG(float g) { Green = clamp(g); };
	inline void setB(float b) { Blue = clamp(b); };
};