#pragma once

#include "figure.h"
namespace Game
{
	class LogicBoard;

	// ���������� ���� �����, ������� ������ ����� ���������
	class SpecialMove
	{
	protected:
		// �������� � �����
		LogicBoard * m_board;
		// ������������� ������
		Figure * m_moving_figure;
		// c-tor
		SpecialMove(LogicBoard * board, Figure * moving_figure) 
			: m_board(board), m_moving_figure(moving_figure)
		{ }
	public:

		// ���������� ����
		virtual void complete () = 0;

		// ��������� ������������� ������
		void setMovingFigure(Figure * figure) { m_moving_figure = figure; }
	};
}

