#pragma once

#include "command.h"
#include "chess-game.h"

// ���������� ������� ��� ������� ����


// ������ PLAY
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

// ������ QUIT
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