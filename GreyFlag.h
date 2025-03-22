#pragma once
#include "Actor.h"
#include "MeshComponent.h"

class GreyFlag : public Actor
{
public:
	GreyFlag(GAME_ObjectID objectId) : Actor(objectId)
	{
		CreateComponent<MeshComponent>("Resources/test.obj", "Resources/Grey.png");
	}
};