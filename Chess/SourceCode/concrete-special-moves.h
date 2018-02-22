#pragma once

#include "stdafx.h"
#include "special-move.h"

/*
	Все конкретные ходы, которые фигру могут создать
	Реализуют интерфейс SpecialMove, должны уметь себя выполнять методом void complete()
*/

namespace Game
{

	class FigureFactory;


	// Захват фигуры
	class CaptureFigureMove : public SpecialMove
	{
		const sf::Vector2i& m_new_pos;
	public:
		void complete();
		CaptureFigureMove(LogicBoard * board, Figure * moving_figure, const sf::Vector2i& new_pos);
	};


	// Простой ход в пустую клетку
	class InEmptyCellMove : public SpecialMove
	{
		const sf::Vector2i& m_new_pos;
	public:
		void complete();
		InEmptyCellMove(LogicBoard * board, Figure * moving_figure, const sf::Vector2i& new_pos);
	};


	/* Комбинация первых двух в зависимости от клетки-назначения
		если клетка пустая - ход в пустую клетку, если заполнена - захват фигуры
	*/
	class GeneralMove : public SpecialMove
	{
		const sf::Vector2i& m_new_pos;
	public:
		void complete();
		GeneralMove(LogicBoard * board, Figure * moving_figure, const sf::Vector2i& new_pos);
	};


	// Преобразование пешки в ферзя
	class PawnTransformMove : public SpecialMove
	{
		const sf::Vector2i& m_new_pos;
		SpecialMove * m_addition_move;
	public:
		void complete();
		PawnTransformMove(LogicBoard *, SpecialMove *, Figure * , const sf::Vector2i& new_pos);
		~PawnTransformMove(){delete m_addition_move;}
	};


	// Рокировка
	class CastlingMove : public SpecialMove
	{
		const sf::Vector2i  m_king_new_pos, m_rook_new_pos;
		Figure * m_ally_rook;
	public:
		void complete();
		CastlingMove(LogicBoard * board, Figure * const king, const sf::Vector2i& king_pos, Figure * const rook, const sf::Vector2i& rook_pos);
	};


}
