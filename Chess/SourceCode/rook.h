#pragma once

#include "figure.h"

namespace Game
{
	// ������ - �����
	class Rook : public Game::Figure
	{
	public:
		// ����������� �� �����������
		using Game::Figure::Figure;
		~Rook() {}
		// �������� ���� �� ����� ��������
		bool createMove(SpecialMove ** move, const sf::Vector2i& new_pos);
		// ������ �� �����, ��� ���
		bool isFirstMove() { return is_first_move; }
	private:
		bool is_first_move = true;
	};
}
