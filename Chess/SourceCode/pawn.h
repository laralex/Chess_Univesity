#pragma once

#include "figure.h"

namespace Game
{
	// Фигруа - ПЕШКА
	class Pawn : public Game::Figure
	{
	public:
		// Имеет определенное направление передвижения
		Pawn(int direction) : moving_direction(direction) {}
		~Pawn() {}
		// Создание хода по своим правилам
		bool createMove(SpecialMove ** move, const sf::Vector2i& new_pos);
	private:
		int  moving_direction = 1;
		bool is_first_move = true;
	};
}
