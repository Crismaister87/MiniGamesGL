#pragma once
#include "LMatrix.h"

class ProjectionMatrix : public LMatrix<float>
{
private:
	float VerticalFOV;
	float ScreenWidth;
	float ScreenHeight;
	float zNear;
	float zFar;

public:
	ProjectionMatrix(float verticalFov, float screenWidth, float screenHeight, float near, float far) : LMatrix(4, 4),
		VerticalFOV(verticalFov), ScreenWidth(screenWidth), ScreenHeight(screenHeight), zNear(near), zFar(far)
	{
		for (size_t i = 0; i < NumRows * NumCols; ++i) {
			Data[i] = 0.0f;
		}
		RecompileMatrix();
	};

	void SetFOV(float verticalFov)
	{
		VerticalFOV = verticalFov;
		RecompileMatrix();
	}

	void SetScreenSize(float screenWidth, float screenHeight)
	{
		ScreenWidth = screenWidth;
		ScreenHeight = screenHeight;
		RecompileMatrix();
	}

	void SetZNear(float near)
	{
		zNear = near;
		RecompileMatrix();
	}

	void SetZFar(float far)
	{
		zFar = far;
		RecompileMatrix();
	}

	void RecompileMatrix()
	{
		float FOV = tan(VerticalFOV / 2);
		Data[0] = ScreenHeight / (ScreenWidth * FOV);
		Data[5] = 1 / FOV;
		Data[10] = -(zFar + zNear) / (zFar - zNear);
		Data[14] = -(2 * zFar * zNear) / (zFar - zNear);
		Data[11] = -1;
	}
};