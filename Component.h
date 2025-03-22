#pragma once
#include <memory>

class Component
{
public:
	virtual void Update() {};
	virtual bool IsRenderable() { return false; };
	virtual void Render(unsigned int transformMatrixId) = 0;
};