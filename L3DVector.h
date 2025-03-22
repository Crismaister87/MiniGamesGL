#pragma once
#include "LVector.h"

#define L3DVECTOR_IDENTITY {1,1,1}
#define L3DVECTOR_ZERO {0,0,0}

class L3DVector : public LVector<float>
{
public:
	L3DVector() : LVector(0.0f, 0.0f, 0.0f, 0.0f) {};
	L3DVector(float inX, float inY, float inZ) : LVector(inX, inY, inZ, 1.0f) {};

	L3DVector cross(L3DVector& inOtherVector)
	{
		L3DVector result(0.0f, 0.0f, 0.0f);
		result[0] = Data[1] * inOtherVector[2] - Data[2] * inOtherVector[0];
		result[1] = Data[2] * inOtherVector[0] - Data[0] * inOtherVector[2];
		result[2] = Data[0] * inOtherVector[1] - Data[1] * inOtherVector[0];
		return result;
	}

	inline float getX() const { return Data[0]; };
	inline float getY() const { return Data[1]; };
	inline float getZ() const { return Data[2]; };

	inline void set(float newX, float newY, float newZ) { Data[0] = newX; Data[1] = newY; Data[2] = newZ;};
	inline void setX(float newX) { Data[0] = newX; };
	inline void setY(float newY) { Data[1] = newY; };
	inline void setZ(float newZ) { Data[2] = newZ; };
};