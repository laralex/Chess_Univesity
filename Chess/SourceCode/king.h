#pragma once

#include "figure.h"

namespace Game
{
	// ������ - ������
	class King : public Game::Figure
	{
		bool is_first_move = true;
	public:
		// ����������� �� �����������
		using Game::Figure::Figure;
		// ���������� �������� ����� ����
		~King();
		// �������� ���� �� ����� ��������
		bool createMove(SpecialMove ** move, const sf::Vector2i& new_pos);
	};
}

