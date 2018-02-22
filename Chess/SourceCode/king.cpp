#include "stdafx.h"
#include "king.h"
#include "logic-board.h"
#include "concrete-special-moves.h"

using namespace Game;

King::~King()
{
	m_board->end();
}

bool King::createMove(SpecialMove ** move, const sf::Vector2i& new_pos)
{
	sf::Vector2i diff = new_pos - m_pos;
	int absx = abs(diff.x), absy = abs(diff.y);
	Rook * rook;
	if (absx <= 1 && absy <= 1)
		*move = new GeneralMove(m_board, this, new_pos); // Обычный	ход
	else if (is_first_move && absx == 2 && absy == 0)
	{
		// Проверка на рокировку
		int dx;
		// Между нами и ладьей пусто
		if (diff.x == -2)
		{
			dx = 0;
			for(int i = 1; i < 4; ++i) 
				if (m_board->isNonEmptyCell(sf::Vector2i(i,m_pos.y)))
				return false;
		}
		else
		{
			dx = 7;
			for (int i = 5; i < 7; ++i)
				if (m_board->isNonEmptyCell(sf::Vector2i(i, m_pos.y)))
					return false;
		}
		rook = dynamic_cast<Rook*>(m_board->getFigure(sf::Vector2i(dx, new_pos.y)));
		if (rook->isFirstMove())
		{
			// Рокировка
			*move = new CastlingMove(m_board, this, new_pos, rook, sf::Vector2i(new_pos.x + (diff.x == -2 ? 1 : -1), new_pos.y)); 
		}
		else
			return false;
	}
	else 
		return false;
	if (is_first_move) is_first_move = false;
	return true;
}