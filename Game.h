#pragma once

#include "GLGame.h"

#include "Command.h"
#include "Actor.h"
#include "GameManager.h"
#include "SceneManager.h"

#include <iostream>
#include <time.h>
#include <queue>
#include <deque>
#include <GLFW\glfw3.h>

#define INVALIDATE_COMMANDS_DURATION 200

struct CommandData
{
public:
	std::unique_ptr<Command> ReqCommand;
	time_t Timestamp;

	CommandData(std::unique_ptr<Command> inCommand, time_t inTimestamp); 
};

class Game : public GLGame 
{
private:
	time_t LastUpdateTime;
	time_t ElapsedTime;
	time_t FrameTime;

	std::queue<CommandData> CommandQueue;
	std::deque<std::unique_ptr<Command>> ExecutedCommands;

protected:
	void QueueCommand(std::unique_ptr<Command> inCommand, const time_t inTimestamp);
	void HandleInputQueue(const time_t inTimestamp);
	void HandleUndo();

	std::shared_ptr<Actor> Player;	// handle this differently

public:
	Game(GLFWwindow* window, float screenWidth, float screenHeight);
	~Game() { GameManager::get().GetSceneManager()->ClearScene(); };

	void Render();
	void BaseUpdate();
	void InitializeScene();

	void HandleInputBase(int inKey, int inAction, int inModifier);
	virtual void HandleInput(int inKey, int inAction, int inModifier, time_t inTimestamp) = 0;

	void HandleMouseMovement(double xPos, double yPos);
	virtual void HandleMouseMovement(double xPos, double yPos, time_t inTimestamp) = 0;

	virtual void Update(const time_t inCurentTime, const time_t inElapsedTime) = 0;
	virtual void LoadScene() = 0;
};