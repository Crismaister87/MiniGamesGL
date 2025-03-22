#include "MonsterGame.h"
#include "GameManager.h"
#include "SceneManager.h"

#include <GLFW\glfw3.h>
#include <memory>

void MonsterGame::Update(const time_t inCurentTime, const time_t inElapsedTime)
{
	
}

void MonsterGame::LoadScene()
{
	SpawnParameters playerSpawnParameters;
	playerSpawnParameters.position.setX(-0.3f);
	playerSpawnParameters.position.setZ(-0.5f);
	playerSpawnParameters.scale.set(0.1f, 0.1f, 0.1f);
	Player = GameManager::get().GetSceneManager()->SpawnActor("Resources/cube.obj", "Resources/box.png", playerSpawnParameters);	// add the texture to be loaded per object

	SpawnParameters enemySpawnParameters;
	enemySpawnParameters.position.setX(0.3f);
	//enemySpawnParameters.position.setZ(-1.5f);
	enemySpawnParameters.scale.set(0.1f, 0.1f, 1.0f);
	GameManager::get().GetSceneManager()->SpawnActor("Resources/test.obj", "Resources/Grey.png", enemySpawnParameters);

	/*SpawnParameters playerSpawnParameters;
	playerSpawnParameters.position.setX(-0.3f);
	playerSpawnParameters.position.setZ(-0.5f);
	playerSpawnParameters.scale.set(0.1f, 0.1f, 0.3f);
	Player = GameManager::get().GetSceneManager()->SpawnActor("Resources/test.obj", "Resources/box.png", playerSpawnParameters);

	SpawnParameters enemySpawnParameters;
	enemySpawnParameters.position.setX(0.3f);
	enemySpawnParameters.position.setZ(-0.5f);
	enemySpawnParameters.scale.set(0.1f, 0.1f, 0.3f);
	GameManager::get().GetSceneManager()->SpawnActor("Resources/test.obj", "Resources/Grey.png", enemySpawnParameters);*/
}


/***** Commands *****/
void MonsterGame::HandleInput(int inKey, int inAction, int inModifier, time_t inTimestamp)
{
	if (inAction == GLFW_RELEASE)
		return;

	switch (inKey)
	{
	case GLFW_KEY_A:
		QueueCommand(std::make_unique<MoveLeftCommand>(), inTimestamp);
		return;

	case GLFW_KEY_D:
		QueueCommand(std::make_unique<MoveRightCommand>(), inTimestamp);
		return;

	case GLFW_KEY_S:
		QueueCommand(std::make_unique<MoveDownCommand>(), inTimestamp);
		return;

	case GLFW_KEY_W:
		QueueCommand(std::make_unique<MoveUpCommand>(), inTimestamp);
		return;

	case GLFW_KEY_E:
		QueueCommand(std::make_unique<RotateRightCommand>(), inTimestamp);
		return;

	case GLFW_KEY_Q:
		QueueCommand(std::make_unique<RotateLeftCommand>(), inTimestamp);
		return;

	case GLFW_KEY_U:
		HandleUndo();
		return;
	}
}

void MonsterGame::HandleMouseMovement(double xPos, double yPos, time_t inTimestamp)
{
	if (!MouseInitialized)
	{
		MouseXPos = xPos;
		MouseYPos = yPos;
		MouseInitialized = true;
	}
	else
	{
		double xDelta = xPos - MouseXPos;
		double yDelta = yPos - MouseYPos;

		if(xDelta)
			MainCamera.RotateY(xDelta);

		if (yDelta)
			MainCamera.RotateX(yDelta);

		MouseXPos = xPos;
		MouseYPos = yPos;
	}
}