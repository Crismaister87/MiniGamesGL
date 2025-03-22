#pragma once

#include "Component.h"
#include <iostream>

class GameObject;

//change this to what resource we are loading from file
class MeshComponent : public Component
{
private:
	GameObject* Owner;

	unsigned int IndexOffset;
	unsigned int IndexCount;
	unsigned int TextureId;

public:
	MeshComponent(GameObject* owner, std::string meshPath, std::string texturePath);
	~MeshComponent() { Owner = nullptr; };

	virtual void Render(unsigned int transformMatrixId) override;
	virtual bool IsRenderable() { return true; }
};