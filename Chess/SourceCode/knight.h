#pragma once

#include "figure.h"

namespace Game
{
	// ������ - ����
	class Knight : public Game::Figure
	{
		// ����������� �� �����������
		using Game::Figure::Figure;
		~Knight() {}
		// �������� ���� �� ����� ��������
		bool createMove(SpecialMove ** move, const sf::Vector2i& new_pos);
	};
}
