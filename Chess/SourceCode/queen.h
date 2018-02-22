#pragma once

#include "figure.h"

namespace Game
{
	// ������ - �����
	class Queen : public Game::Figure
	{
		// ����������� �� �����������
		using Game::Figure::Figure;
		~Queen(){}
		// �������� ���� �� ����� ��������
		bool createMove(SpecialMove ** move, const sf::Vector2i& new_pos);
	};
}

