#pragma once
#include "Actor.h"

class Game;
class Command {
public:
	virtual ~Command() = default;

	// do we need game?
	virtual void Execute(std::shared_ptr<Actor> inActor, Game* const inGame) = 0;
	virtual void Undo(std::shared_ptr<Actor> inGameActor, Game* const inGame) = 0;
};