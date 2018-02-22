#pragma once

#include "figure.h"
namespace Game
{
	class LogicBoard;

	// Суперкласс всех ходов, которые фигруы могут совершить
	class SpecialMove
	{
	protected:
		// Привязка к доске
		LogicBoard * m_board;
		// Передвигаемая фигура
		Figure * m_moving_figure;
		// c-tor
		SpecialMove(LogicBoard * board, Figure * moving_figure) 
			: m_board(board), m_moving_figure(moving_figure)
		{ }
	public:

		// Совершение хода
		virtual void complete () = 0;

		// Установка передвигаемой фигуры
		void setMovingFigure(Figure * figure) { m_moving_figure = figure; }
	};
}

