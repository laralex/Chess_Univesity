#pragma once

#include "command.h"
#include "chess-game.h"

// Конкретные команды для пунктов меню


// Кнопка PLAY
class PlayMenuCommand : public Command
{
private:
	ChessGame& game;
public:
	PlayMenuCommand(ChessGame& game) : game(game) {}
	void execute() const
	{
		game.restartGame();
	}
};

// Кнопка QUIT
class ExitMenuCommand : public Command
{
private:
	ChessGame& game;
public:
	ExitMenuCommand(ChessGame& game) : game(game) {}
	void execute() const
	{
		game.exit();
	}
};