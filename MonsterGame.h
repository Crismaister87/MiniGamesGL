#pragma once
#include "Game.h"
#include "Command.h"
#include "Camera.h"

/***** Commands *****/

#define MOVEMENT_SIZE 0.1f

class MoveUpCommand : public Command
{
public:
	void Execute(std::shared_ptr<Actor> inActor, Game* const inGame)
	{
		if (inActor != nullptr && inGame != nullptr) {
			inGame->GetCamera().MoveForward(MOVEMENT_SIZE);
			//inActor->Move(0.0f, MOVEMENT_SIZE, 0.0f);
		}
	}

	void Undo(std::shared_ptr<Actor> inActor, Game* const inGame)
	{
		if (inActor != nullptr && inGame != nullptr) {
			inGame->GetCamera().MoveBackwards(MOVEMENT_SIZE);
			//inActor->Move(0.0f, -MOVEMENT_SIZE, 0.0f);
		}
	}
};

class MoveDownCommand : public Command
{
public:
	void Execute(std::shared_ptr<Actor> inActor, Game* const inGame)
	{
		if (inActor != nullptr && inGame != nullptr) {
			inGame->GetCamera().MoveBackwards(MOVEMENT_SIZE);
			//inActor->Move(0.0f, -MOVEMENT_SIZE, 0.0f);
		}
	}

	void Undo(std::shared_ptr<Actor> inActor, Game* const inGame)
	{
		if (inActor != nullptr && inGame != nullptr) {
			inGame->GetCamera().MoveForward(MOVEMENT_SIZE);
			//inActor->Move(0.0f, MOVEMENT_SIZE, 0.0f);
		}
	}
};

class MoveLeftCommand : public Command
{
public:
	void Execute(std::shared_ptr<Actor> inActor, Game* const inGame)
	{
		if (inActor != nullptr && inGame != nullptr) {
			inGame->GetCamera().MoveLeft(MOVEMENT_SIZE);
			//inActor->Move(-MOVEMENT_SIZE, 0.0f, 0.0f);
		}
	}

	void Undo(std::shared_ptr<Actor> inActor, Game* const inGame)
	{
		if (inActor != nullptr && inGame != nullptr) {
			inGame->GetCamera().MoveRight(MOVEMENT_SIZE);
			//inActor->Move(MOVEMENT_SIZE, 0.0f, 0.0f);
		}
	}
};

class MoveRightCommand : public Command
{
public:
	void Execute(std::shared_ptr<Actor> inActor, Game* const inGame)
	{
		if (inActor != nullptr && inGame != nullptr) {
			inGame->GetCamera().MoveRight(MOVEMENT_SIZE);
			//inActor->Move(MOVEMENT_SIZE, 0.0f, 0.0f);
		}
	}

	void Undo(std::shared_ptr<Actor> inActor, Game* const inGame)
	{
		if (inActor != nullptr && inGame != nullptr) {
			inGame->GetCamera().MoveLeft(MOVEMENT_SIZE);
			//inActor->Move(-MOVEMENT_SIZE, 0.0f, 0.0f);
		}
	}
};

class RotateLeftCommand : public Command
{
public:
	void Execute(std::shared_ptr<Actor> inActor, Game* const inGame)
	{
		if (inActor != nullptr && inGame != nullptr) {
			inGame->GetCamera().RotateZ(MOVEMENT_SIZE);
			//inActor->Move(-MOVEMENT_SIZE, 0.0f, 0.0f);
		}
	}

	void Undo(std::shared_ptr<Actor> inActor, Game* const inGame)
	{
		if (inActor != nullptr && inGame != nullptr) {
			inGame->GetCamera().RotateZ(-MOVEMENT_SIZE);
			//inActor->Move(MOVEMENT_SIZE, 0.0f, 0.0f);
		}
	}
};

class RotateRightCommand : public Command
{
public:
	void Execute(std::shared_ptr<Actor> inActor, Game* const inGame)
	{
		if (inActor != nullptr && inGame != nullptr) {
			inGame->GetCamera().RotateZ(-MOVEMENT_SIZE);
			//inActor->Move(MOVEMENT_SIZE, 0.0f, 0.0f);
		}
	}

	void Undo(std::shared_ptr<Actor> inActor, Game* const inGame)
	{
		if (inActor != nullptr && inGame != nullptr) {
			inGame->GetCamera().RotateZ(MOVEMENT_SIZE);
			//inActor->Move(-MOVEMENT_SIZE, 0.0f, 0.0f);
		}
	}
};


/***** Game *****/

class MonsterGame : public Game {
public:
	MonsterGame(GLFWwindow* window, float screenWidth, float screenHeight) : Game(window, screenWidth, screenHeight) {};

	void Update(const time_t inTimestamp, const time_t iUpdateTime);
	void LoadScene();

	void HandleInput(int inKey, int inAction, int inModifier, time_t inTimestamp);
	void HandleMouseMovement(double xPos, double yPos, time_t inTimestamp);

	double MouseXPos{ 0.0f };
	double MouseYPos{ 0.0f };
	bool MouseInitialized{ false };
};