#pragma once

#include "figure.h"

namespace Game
{
	// Пустая фигура
	class NullFigure : public Game::Figure
	{
	public:
		NullFigure() 
		{
			// Никакого отображения
			setFillColor(sf::Color(0,0,0,0)); 
		}
		~NullFigure() {}
		bool createMove(SpecialMove ** move, const sf::Vector2i& new_pos) 
		{ 
			// Никакого хода
			return false; 
		}
	};
}