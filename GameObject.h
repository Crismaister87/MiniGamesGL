#pragma once

#include "TransformMatrix.h"

typedef unsigned int GAME_ObjectID;

class GameObject
{
private:
	GAME_ObjectID ObjectId;
	TransformMatrix ObjectTransformMatrix;

public:
	GameObject(GAME_ObjectID objectId) : ObjectId(objectId) {};

	inline TransformMatrix& GetTransformation() { return ObjectTransformMatrix; };

	// Translation Matrix
	void SetPosition(const float xLocation, const float yLocation, const float zLocation);
	void SetXPosition(const float xLocation);
	void SetYPosition(const float yLocation);
	void SetZPosition(const float zLocation);
	void Move(const float xDisplacement, const float yDisplacement, const float zDisplacement);


	void SetAngles(const float xAxisRot, const float yAxisRot, const float zAxisRot);
	void SetXAngle(const float xAxisRot);
	void SetYAngle(const float yAxisRot);
	void SetZAngle(const float zAxisRot);
	void Rotate(const float xAxisRot, const float yAxisRot, const float zAxisRot);

	void SetScale(const float xScale, const float yScale, const float zScale);
	void SetXScale(const float xScale);
	void SetYScale(const float yScale);
	void SetZScale(const float zScale);
	void Scale(const float xScale, const float yScale, const float zScale);
};