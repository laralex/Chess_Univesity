#include "stdafx.h"
#include "rook.h"
#include "logic-board.h"
#include "concrete-special-moves.h"

using namespace Game;

bool Rook::createMove(SpecialMove ** move, const sf::Vector2i& new_pos)
{
	sf::Vector2i diff = new_pos - m_pos;
	int dx = 0, dy = 0, limit;
	if (diff.x == 0)
	{
		dy = diff.y > 0 ? 1 : -1;
		limit = abs(diff.y);
	}
	else if (diff.y == 0)
	{
		dx = diff.x > 0 ? 1 : -1;
		limit = abs(diff.x);
	}
	else
		return false;
	for (int i = 1; i < limit; ++i)
	{
		// Все промежуточные клетки должы быть пустыми
		if (m_board->isNonEmptyCell(m_pos + sf::Vector2i(i * dx, i * dy)))
			return false;
	}
	if (is_first_move) is_first_move = false;
	*move = new GeneralMove(m_board, this, new_pos);
	return true;
}