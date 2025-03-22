#pragma once

#include "GameObject.h"
#include "L3DVector.h"
#include "RGBColor.h"
#include "TransformMatrix.h"

#include "Component.h"
#include <vector>

#include <glm/gtc/matrix_transform.hpp>

class MeshComponent;

class GLGame;

class Actor : public GameObject {
private:
	unsigned int IndexOffset;
	unsigned int IndexCount;

	bool IsTextured;
	unsigned int TextureId;

	std::vector<std::shared_ptr<Component>> Components;

public:
	Actor(GAME_ObjectID objectId, unsigned int indexOffset, unsigned int indexCount, bool isTextured, unsigned int textureId);
	~Actor() { Components.clear(); };

	void Render(unsigned int transformMatrixId);
	void PrintDebugCoordinates();
};