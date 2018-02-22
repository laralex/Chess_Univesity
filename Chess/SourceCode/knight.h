#pragma once

#include "figure.h"

namespace Game
{
	// Фигура - КОНЬ
	class Knight : public Game::Figure
	{
		// Конструктор из суперкласса
		using Game::Figure::Figure;
		~Knight() {}
		// Создание хода по своим правилам
		bool createMove(SpecialMove ** move, const sf::Vector2i& new_pos);
	};
}
