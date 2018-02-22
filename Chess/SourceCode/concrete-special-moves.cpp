
#include "stdafx.h"
#include "concrete-special-moves.h"
#include "logic-board.h"
// REMOVE
#include "figure-factory.h"
//
using namespace Game;

CaptureFigureMove::CaptureFigureMove
(LogicBoard * board, Figure * const moving_figure, const sf::Vector2i& new_pos)
	: SpecialMove(board, moving_figure), m_new_pos(new_pos)
{

}

void CaptureFigureMove::complete()
{
	// Удаляем фигуру
	m_board->captureFigure(m_new_pos);
	// Ходим в получившуюся пустую клетку
	InEmptyCellMove empty_move(m_board, m_moving_figure, m_new_pos);
	empty_move.complete();
}

InEmptyCellMove::InEmptyCellMove
(LogicBoard * board, Figure * const moving_figure, const sf::Vector2i& new_pos)
	: SpecialMove(board, moving_figure), m_new_pos(new_pos)
{

}

void InEmptyCellMove::complete()
{
	// Ходим в пустую клетку (обмен нашей фигуры и пустой фигуры)
	m_board->swapFigures(m_moving_figure, m_board->getFigure(m_new_pos));
	m_board->updateVisualState(m_moving_figure);
}

PawnTransformMove::PawnTransformMove
(LogicBoard * board, SpecialMove * undecorated_move, Figure * moving_figure, const sf::Vector2i& new_pos)
	: SpecialMove(board, moving_figure), m_addition_move(undecorated_move), m_new_pos(new_pos)
{

}

void PawnTransformMove::complete()
{
	// Преобразуем пешку
	Figure * transformed_pawn = m_board->transformPawn(m_moving_figure);
	// Совершаем ход бывшей пешки
	m_addition_move->setMovingFigure(transformed_pawn);
	m_addition_move->complete();
}

GeneralMove::GeneralMove
(LogicBoard * board, Figure * const moving_figure, const sf::Vector2i& new_pos)
	: SpecialMove(board, moving_figure), m_new_pos(new_pos)
{
	
}

void GeneralMove::complete()
{
	// На клетке есть противник
	if (m_board->isNonEmptyCell(m_new_pos))
		CaptureFigureMove(m_board, m_moving_figure, m_new_pos).complete();
	// Клетка пустая
	else
		InEmptyCellMove(m_board, m_moving_figure, m_new_pos).complete();
}

CastlingMove::CastlingMove(LogicBoard * board, Figure * const moving_king, const sf::Vector2i& king_new_pos, Figure * const ally_rook, const sf::Vector2i& rook_new_pos)
	: SpecialMove(board, moving_king), m_ally_rook(ally_rook), m_king_new_pos(king_new_pos), m_rook_new_pos(rook_new_pos)
{

}

void CastlingMove::complete()
{
	// Переносим короля и ладью
	InEmptyCellMove(m_board, m_moving_figure, m_king_new_pos).complete();
	InEmptyCellMove(m_board, m_ally_rook, m_rook_new_pos).complete();
}