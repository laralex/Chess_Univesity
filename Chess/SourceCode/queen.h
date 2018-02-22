#pragma once

#include "figure.h"

namespace Game
{
	// Фигура - ФЕРЗЬ
	class Queen : public Game::Figure
	{
		// Конструктор из суперкласса
		using Game::Figure::Figure;
		~Queen(){}
		// Создание хода по своим правилам
		bool createMove(SpecialMove ** move, const sf::Vector2i& new_pos);
	};
}

