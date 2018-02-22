#pragma once

#include "figure.h"

namespace Game
{
	// Фигруа - ЛАДЬЯ
	class Rook : public Game::Figure
	{
	public:
		// Конструктор из суперкласса
		using Game::Figure::Figure;
		~Rook() {}
		// Создание хода по своим правилам
		bool createMove(SpecialMove ** move, const sf::Vector2i& new_pos);
		// Ходила ли ладья, или нет
		bool isFirstMove() { return is_first_move; }
	private:
		bool is_first_move = true;
	};
}
