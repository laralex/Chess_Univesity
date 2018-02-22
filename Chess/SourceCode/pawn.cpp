#include "stdafx.h"
#include "pawn.h"
#include "logic-board.h"
#include "concrete-special-moves.h"

using namespace Game;

bool Pawn::createMove(SpecialMove ** move, const sf::Vector2i& new_pos)
{
	sf::Vector2i diff = new_pos - m_pos;
	// Сдвиг на 1 в направлении движения пешки
	if (diff.y == moving_direction) 
	{
		if (abs(diff.x) == 1 && m_board->isNonEmptyCell(new_pos))
			*move = new CaptureFigureMove(m_board, this, new_pos); // Захват фигуры по диагонали на 1 клетку
		else if (abs(diff.x) == 0 && !m_board->isNonEmptyCell(new_pos))
			*move = new InEmptyCellMove(m_board, this, new_pos); // Ход вперед на 1 клетку
		else  return false;
			
		if (new_pos.y == ((moving_direction == 1) ? 7 : 0)) 
			*move = new PawnTransformMove(m_board, *move, this, new_pos); // Пешка дошла до конца - превращаем в ферзя
	}
	// Сдвиг на 2 в направлении движения пешки при первом ходе
	else if (is_first_move && diff.y == 2 * moving_direction && abs(diff.x) == 0) 
		*move = new InEmptyCellMove(m_board, this, new_pos); // Первый ход на 2 клетки вперед
	else
		return false;
	if (is_first_move) is_first_move = false;
	return true;
}