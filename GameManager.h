#pragma once

#include <memory>

class SceneManager;
class ResourceManager;

class Game;

class GameManager
{
public:
	static GameManager& get()
	{
		static GameManager* instance = new GameManager;
		return *instance;
	}

	inline std::shared_ptr<SceneManager> GetSceneManager() { return GameSceneManager; };
	inline std::shared_ptr<ResourceManager> GetResourceManager() { return GameResourceManager; };
	
	void LinkGame(Game* ptr) { GamePtr.reset(ptr); };
	std::shared_ptr<Game> GetGamePtr() { return GamePtr; };

private:
	std::shared_ptr<Game> GamePtr;
	std::shared_ptr<SceneManager> GameSceneManager;
	std::shared_ptr<ResourceManager> GameResourceManager;

	GameManager();
};