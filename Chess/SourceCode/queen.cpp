#include "stdafx.h"
#include "queen.h"
#include "logic-board.h"
#include "concrete-special-moves.h"

using namespace Game;

bool Queen::createMove(SpecialMove ** move, const sf::Vector2i& new_pos)
{
	sf::Vector2i diff = new_pos - m_pos;
	int dx = 0, dy = 0,
		absx = abs(diff.x), absy = abs(diff.y), limit = absy;
	if (diff.x)
		dx = diff.x / absx;
	if (diff.y)
		dy = diff.y / absy;
	if (diff.y == 0)
		limit = absx;
	if (absx != absy && dx*dy != 0)
		return false;
	for (int i = 1; i < limit; ++i)
	{
		// Все промежуточные клетки должы быть пустыми
		if (m_board->isNonEmptyCell(m_pos + sf::Vector2i(i * dx, i * dy)))
			return false;
	}
	*move = new GeneralMove(m_board, this, new_pos);
	return true;
}