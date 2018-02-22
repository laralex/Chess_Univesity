#pragma once

#include "figure.h"

namespace Game
{
	// ������ - ����
	class Bishop : public Game::Figure
	{
		// ����������� �� �����������
		using Game::Figure::Figure;
		~Bishop() {}
		// �������� ���� �� ����� ��������
		bool createMove(SpecialMove ** move, const sf::Vector2i& new_pos);
	};
}

