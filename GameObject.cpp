#include "GameObject.h"

/***** Position *****/
void GameObject::SetPosition(const float xLocation, const float yLocation, const float zLocation)
{
	ObjectTransformMatrix.SetXTranslation(xLocation);
	ObjectTransformMatrix.SetYTranslation(yLocation);
	ObjectTransformMatrix.SetZTranslation(zLocation);
}

void GameObject::SetXPosition(const float xLocation)
{
	ObjectTransformMatrix.SetXTranslation(xLocation);
}

void GameObject::SetYPosition(const float yLocation)
{
	ObjectTransformMatrix.SetYTranslation(yLocation);
}

void GameObject::SetZPosition(const float zLocation)
{
	ObjectTransformMatrix.SetZTranslation(zLocation);
}

void GameObject::Move(const float xDisplacement, const float yDisplacement, const float zDisplacement)
{
	ObjectTransformMatrix.SetXTranslation(ObjectTransformMatrix.GetXTranslation() + xDisplacement);
	ObjectTransformMatrix.SetYTranslation(ObjectTransformMatrix.GetYTranslation() + yDisplacement);
	ObjectTransformMatrix.SetZTranslation(ObjectTransformMatrix.GetZTranslation() + zDisplacement);
}

/***** Rotation *****/
void GameObject::SetAngles(const float xAxisRot, const float yAxisRot, const float zAxisRot)
{
	ObjectTransformMatrix.SetAngles(xAxisRot, yAxisRot, zAxisRot);
}

void GameObject::SetXAngle(const float xAxisRot)
{
	ObjectTransformMatrix.SetXAngle(xAxisRot);
}

void GameObject::SetYAngle(const float yAxisRot)
{
	ObjectTransformMatrix.SetYAngle(yAxisRot);
}

void GameObject::SetZAngle(const float zAxisRot)
{
	ObjectTransformMatrix.SetZAngle(zAxisRot);
}

void GameObject::Rotate(const float xAxisRot, const float yAxisRot, const float zAxisRot)
{
	ObjectTransformMatrix.SetAngles(ObjectTransformMatrix.GetXAngle() + xAxisRot, ObjectTransformMatrix.GetYAngle() + yAxisRot, ObjectTransformMatrix.GetZAngle() + zAxisRot);
}

/***** Scale *****/
void GameObject::SetScale(const float xScale, const float yScale, const float zScale)
{
	ObjectTransformMatrix.SetScale(xScale, yScale, zScale);
}

void GameObject::SetXScale(const float xScale)
{
	ObjectTransformMatrix.SetXScale(xScale);
}

void GameObject::SetYScale(const float yScale)
{
	ObjectTransformMatrix.SetYScale(yScale);
}

void GameObject::SetZScale(const float zScale)
{
	ObjectTransformMatrix.SetZScale(zScale);
}

void GameObject::Scale(const float xScale, const float yScale, const float zScale)
{
	ObjectTransformMatrix.SetScale(ObjectTransformMatrix.GetXScale() + xScale, ObjectTransformMatrix.GetYScale() + yScale, ObjectTransformMatrix.GetZScale() + zScale);
}