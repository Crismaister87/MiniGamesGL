#pragma once
#include "LVector.h"

class L2DVector : public LVector<float>
{
public:

	L2DVector() : LVector(0.0f, 0.0f, 0.0f) {};
	L2DVector(float inX, float inY) : LVector(inX, inY, 0.0f) {};

	float cross(L2DVector& inOtherVector)
	{
		return Data[0] * inOtherVector[1] - Data[1] * inOtherVector[0];
	}

	float X() { return Data[0]; };
	float Y() { return Data[1]; };
};