#pragma once

#include "figure.h"

namespace Game
{
	// ������ - �����
	class Pawn : public Game::Figure
	{
	public:
		// ����� ������������ ����������� ������������
		Pawn(int direction) : moving_direction(direction) {}
		~Pawn() {}
		// �������� ���� �� ����� ��������
		bool createMove(SpecialMove ** move, const sf::Vector2i& new_pos);
	private:
		int  moving_direction = 1;
		bool is_first_move = true;
	};
}
