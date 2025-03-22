#pragma once
#include "Actor.h"
#include "MeshComponent.h"

class Box : public Actor
{
public:
	Box(GAME_ObjectID objectId) : Actor(objectId)
	{
		CreateComponent<MeshComponent>("Resources/cube.obj", "Resources/Grey.png");
	}
};