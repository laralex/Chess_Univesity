#pragma once

#include "figure.h"

namespace Game
{
	// Фигура - СЛОН
	class Bishop : public Game::Figure
	{
		// Конструктор из суперкласса
		using Game::Figure::Figure;
		~Bishop() {}
		// Создание хода по своим правилам
		bool createMove(SpecialMove ** move, const sf::Vector2i& new_pos);
	};
}

