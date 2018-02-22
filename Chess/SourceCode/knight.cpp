#include "stdafx.h"
#include "knight.h"
#include "logic-board.h"
#include "concrete-special-moves.h"

using namespace Game;

bool Knight::createMove(SpecialMove ** move, const sf::Vector2i& new_pos)
{
	sf::Vector2i diff = new_pos - m_pos;
	int absx = abs(diff.x), absy = abs(diff.y);
	// Ходим буквой Г
	if (absx == 1 && absy == 2 || absx == 2 && absy == 1)
	{
		*move = new GeneralMove(m_board, this, new_pos);
		return true;
	}
	return false;
}