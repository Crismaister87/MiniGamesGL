#pragma once

#include "Component.h"
#include <iostream>

//change this to what resource we are loading from file
class MeshComponent : public Component
{
private:
	unsigned int IndexOffset;
	unsigned int IndexCount;

public:
	MeshComponent(std::string meshPath, std::string texturePath);
	~MeshComponent() { };

	virtual void Render(unsigned int transformMatrixId) override;
	virtual bool IsRenderable() { return true; }
};