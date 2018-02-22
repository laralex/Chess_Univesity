#include "stdafx.h"
#include "chess-game.h"

int main(int argc, TCHAR *argv[])
{
	ChessGame& chess = ChessGame::getInstance();
	chess.launch();
	return 0;
}