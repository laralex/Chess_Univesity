#pragma once

#include "figure.h"

namespace Game
{
	// Фигура - КОРОЛЬ
	class King : public Game::Figure
	{
		bool is_first_move = true;
	public:
		// Конструктор из суперкласса
		using Game::Figure::Figure;
		// Деструктор вызывает конец игры
		~King();
		// Создание хода по своим правилам
		bool createMove(SpecialMove ** move, const sf::Vector2i& new_pos);
	};
}

