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
	std::shared_ptr<Actor> SpawnActor(std::string meshPath, std::string texturePath, SpawnParameters& spawnParameters);
	void ClearScene() { GameObjects.clear(); };
};