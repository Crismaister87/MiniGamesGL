#pragma once
#include "LMatrix.h"

class TransformMatrix : public LMatrix<float>
{
private:
	float xAngle{ 0.0f };
	float sinXAngle{ 0.0f };
	float cosXAngle{ 1.0f };

	float yAngle{ 0.0f };
	float sinYAngle{ 0.0f };
	float cosYAngle{ 1.0f };

	float zAngle{ 0.0f };
	float sinZAngle{ 0.0f };
	float cosZAngle{ 1.0f };

	float xScale{ 1.0f };
	float yScale{ 1.0f };
	float zScale{ 1.0f };

public:
	TransformMatrix() : LMatrix(4, 4)
	{
		for (size_t i = 0; i < NumRows * NumCols; ++i) {
			Data[i] = 0.0f;
		}

		Data[0] = 1.0f;
		Data[5] = 1.0f;
		Data[10] = 1.0f;
		Data[15] = 1.0f;
	};

	void RecompileMatrix()
	{
		Data[0] = xScale * cosYAngle * cosZAngle;
		Data[4] = yScale * (cosZAngle * sinYAngle * sinXAngle - sinZAngle * cosXAngle);
		Data[8] = zScale * (cosZAngle * sinYAngle * cosXAngle + sinZAngle * sinXAngle);

		Data[1] = xScale * sinZAngle * cosYAngle;
		Data[5] = yScale * (sinZAngle * sinYAngle * sinXAngle + cosZAngle * cosXAngle);
		Data[9] = zScale * (sinZAngle * sinYAngle * cosXAngle - cosZAngle * sinXAngle);

		Data[2] = -xScale * sinYAngle;
		Data[6] = yScale * cosYAngle * sinXAngle;
		Data[10] = zScale * cosYAngle * cosXAngle;
	}

	/***** Setters *****/
	inline void SetXAngle(float angle)
	{
		xAngle = angle;
		sinXAngle = sin(angle);
		cosXAngle = cos(angle);
		RecompileMatrix();
	}

	inline void SetYAngle(float angle)
	{
		yAngle = angle;
		sinYAngle = sin(angle);
		cosYAngle = cos(angle);
		RecompileMatrix();
	}

	inline void SetZAngle(float angle)
	{
		zAngle = angle;
		sinZAngle = sin(angle);
		cosZAngle = cos(angle);
		RecompileMatrix();
	}

	inline void SetAngles(float angleX, float angleY, float angleZ)
	{
		xAngle = angleX;
		sinXAngle = sin(angleX);
		cosXAngle = cos(angleX);

		yAngle = angleY;
		sinYAngle = sin(angleY);
		cosYAngle = cos(angleY);

		zAngle = angleZ;
		sinZAngle = sin(angleZ);
		cosZAngle = cos(angleZ);

		RecompileMatrix();
	}

	inline void SetXScale(float scale) { xScale = scale < 0 ? -scale : scale; RecompileMatrix(); };
	inline void SetYScale(float scale) { yScale = scale < 0 ? -scale : scale; RecompileMatrix(); };
	inline void SetZScale(float scale) { zScale = scale < 0 ? -scale : scale; RecompileMatrix(); };

	inline void SetScale(float inXScale, float inYScale, float inZScale)
	{
		xScale = inXScale < 0.0f ? -inXScale : inXScale;
		yScale = inYScale < 0.0f ? -inYScale : inYScale;
		zScale = inZScale < 0.0f ? -inZScale : inZScale;

		RecompileMatrix();
	}

	inline void SetXTranslation(float translation) { Data[12] = translation; };
	inline void SetYTranslation(float translation) { Data[13] = translation; };
	inline void SetZTranslation(float translation) { Data[14] = translation; };

	/***** Setters *****/
	inline float GetXAngle() { return xAngle; };
	inline float GetYAngle() { return yAngle; };
	inline float GetZAngle() { return zAngle; };

	inline float GetXScale() { return xScale; };
	inline float GetYScale() { return yScale; };
	inline float GetZScale() { return zScale; };

	inline float GetXTranslation() { return Data[12]; };
	inline float GetYTranslation() { return Data[13]; };
	inline float GetZTranslation() { return Data[14]; };
};