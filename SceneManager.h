#pragma once

#include <string>
#include <vector>
#include <memory>

#include "Actor.h"

class Game;
struct SpawnParameters
{
	L3DVector position = L3DVECTOR_ZERO;
	L3DVector rotation = L3DVECTOR_ZERO;
	L3DVector scale = L3DVECTOR_IDENTITY;
};

class SceneManager
{
private:
	std::vector<std::shared_ptr<Actor>> GameObjects;

public:
	SceneManager() {};
	~SceneManager() { ClearScene(); };

	void RenderSceneObjects(unsigned int transformationMatrixID);
	void ClearScene() { GameObjects.clear(); };

	template<class T>
	std::shared_ptr<Actor> SpawnActor(SpawnParameters& spawnParameters)
	{
		std::shared_ptr<Actor> newActor = std::make_shared<T>(0);	// use id as you should, GameObjects map?
		newActor->SetPosition(spawnParameters.position.getX(), spawnParameters.position.getY(), spawnParameters.position.getZ());
		newActor->SetAngles(spawnParameters.rotation.getX(), spawnParameters.rotation.getY(), spawnParameters.rotation.getZ());
		newActor->SetScale(spawnParameters.scale.getX(), spawnParameters.scale.getY(), spawnParameters.scale.getZ());

		GameObjects.push_back(newActor);
		return newActor;
	}
};