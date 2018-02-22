#pragma once

#include "figure.h"

namespace Game
{
	// ������ ������
	class NullFigure : public Game::Figure
	{
	public:
		NullFigure() 
		{
			// �������� �����������
			setFillColor(sf::Color(0,0,0,0)); 
		}
		~NullFigure() {}
		bool createMove(SpecialMove ** move, const sf::Vector2i& new_pos) 
		{ 
			// �������� ����
			return false; 
		}
	};
}