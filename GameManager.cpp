#include "GameManager.h"
#include "SceneManager.h"
#include "ResourceManager.h"

GameManager::GameManager()
{
	GameSceneManager = std::make_shared<SceneManager>();
	GameResourceManager = std::make_shared<ResourceManager>();
}