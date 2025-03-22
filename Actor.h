#pragma once

#include "GameObject.h"
#include "L3DVector.h"
#include "RGBColor.h"
#include "TransformMatrix.h"

#include "Component.h"
#include <vector>

#include <glm/gtc/matrix_transform.hpp>

class GLGame;
class Component;

class Actor : public GameObject {
protected:
	std::vector<std::shared_ptr<Component>> Components;

public:
	Actor(GAME_ObjectID objectId) : GameObject(objectId) {};
	~Actor() { Components.clear(); };

	void Render(unsigned int transformMatrixId);
	void PrintDebugCoordinates();

	template<typename T, typename...Args>
	std::shared_ptr<T> CreateComponent(Args&&... args)
	{
		std::shared_ptr<T> ptr = std::make_shared<T>(this, std::forward<Args>(args)...);
		Components.push_back(ptr);
		return ptr;
	}
};

