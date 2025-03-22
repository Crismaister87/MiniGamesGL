#include "Game.h"
#include "Command.h"
#include "GameManager.h"
#include "ResourceManager.h"
#include "SceneManager.h"

#include <chrono>

#define MS_PER_UPDATE 16

using Clock = std::chrono::steady_clock;

CommandData::CommandData(std::unique_ptr<Command> inCommand, time_t inTimestamp) : ReqCommand(std::move(inCommand)), Timestamp(inTimestamp) {};

Game::Game(GLFWwindow* window, float screenWidth, float screenHeight) : GLGame(window)
{
	GameManager::get().LinkGame(this);
	InitializeGL(screenWidth, screenHeight);

	auto clockNow = Clock::now();
	time_t timeNow = std::chrono::duration_cast<std::chrono::milliseconds>(clockNow.time_since_epoch()).count();
	LastUpdateTime = timeNow;

	ElapsedTime = 0;
	FrameTime = 0;
}

void Game::HandleInputBase(int inKey, int inAction, int inModifier)
{
	auto clockNow = Clock::now();
	time_t timeNow = std::chrono::duration_cast<std::chrono::milliseconds>(clockNow.time_since_epoch()).count();

	if (inKey == GLFW_KEY_ESCAPE)
	{
		glfwSetWindowShouldClose(GLWindow, GLFW_TRUE);
		return;
	}

	HandleInput(inKey, inAction, inModifier, timeNow);
}

void Game::HandleMouseMovement(double xPos, double yPos)
{
	auto clockNow = Clock::now();
	time_t timeNow = std::chrono::duration_cast<std::chrono::milliseconds>(clockNow.time_since_epoch()).count();

	HandleMouseMovement(xPos, yPos, timeNow);
}

void Game::QueueCommand(std::unique_ptr<Command> inCommand, const time_t inTimestamp)
{
	CommandQueue.push({ std::move(inCommand), inTimestamp });
}

void Game::BaseUpdate()
{
	auto clockNow = Clock::now();
	time_t timeNow = std::chrono::duration_cast<std::chrono::milliseconds>(clockNow.time_since_epoch()).count();

	HandleInputQueue(timeNow);

	FrameTime += timeNow - LastUpdateTime;
	while (FrameTime > MS_PER_UPDATE)
	{
		ElapsedTime += MS_PER_UPDATE;
		Update(ElapsedTime, MS_PER_UPDATE);
		FrameTime -= MS_PER_UPDATE;
	}
	LastUpdateTime = timeNow;
}

void Game::InitializeScene()
{
	LoadScene();
	GameManager::get().GetResourceManager()->LoadVertexBufferData();
	GameManager::get().GetResourceManager()->LoadIndexBufferData();
}

void Game::HandleInputQueue(const time_t inTimestamp)
{
	while (!CommandQueue.empty())
	{
		if (inTimestamp - CommandQueue.front().Timestamp > INVALIDATE_COMMANDS_DURATION)
		{
			CommandQueue.pop();
		}
		else
		{
			CommandQueue.front().ReqCommand.get()->Execute(Player, this);
			ExecutedCommands.push_back(std::move(CommandQueue.front().ReqCommand));
			CommandQueue.pop();
		}
	}
}

void Game::HandleUndo()
{
	if (ExecutedCommands.size() > 0)
	{
		ExecutedCommands.back()->Undo(Player, this);
		ExecutedCommands.pop_back();
	}
}

void Game::Render()
{
	GLDraw();
	GameManager::get().GetSceneManager()->RenderSceneObjects(TransformMatrixId);
}