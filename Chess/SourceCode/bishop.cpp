#include "stdafx.h"
#include "bishop.h"
#include "logic-board.h"
#include "concrete-special-moves.h"

using namespace Game;

bool Bishop::createMove(SpecialMove ** move, const sf::Vector2i& new_pos)
{
	sf::Vector2i diff = new_pos - m_pos;
	int dx = diff.x > 0 ? 1 : -1, dy = diff.y  > 0 ? 1 : -1, absx = abs(diff.x);
	if (absx != abs(diff.y)) // Только диагональные перемещения
		return false;
	for (int i = 1; i < absx; ++i)
	{
		// Все промежуточные клетки должы быть пустыми
		if (m_board->isNonEmptyCell(m_pos + sf::Vector2i(i * dx, i * dy)))
			return false;
	}
	// Обычный ход по диагонали
	*move = new GeneralMove(m_board, this, new_pos);
	return true;
}