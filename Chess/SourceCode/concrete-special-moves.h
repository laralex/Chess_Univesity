#pragma once

#include "stdafx.h"
#include "special-move.h"

/*
	��� ���������� ����, ������� ����� ����� �������
	��������� ��������� SpecialMove, ������ ����� ���� ��������� ������� void complete()
*/

namespace Game
{

	class FigureFactory;


	// ������ ������
	class CaptureFigureMove : public SpecialMove
	{
		const sf::Vector2i& m_new_pos;
	public:
		void complete();
		CaptureFigureMove(LogicBoard * board, Figure * moving_figure, const sf::Vector2i& new_pos);
	};


	// ������� ��� � ������ ������
	class InEmptyCellMove : public SpecialMove
	{
		const sf::Vector2i& m_new_pos;
	public:
		void complete();
		InEmptyCellMove(LogicBoard * board, Figure * moving_figure, const sf::Vector2i& new_pos);
	};


	/* ���������� ������ ���� � ����������� �� ������-����������
		���� ������ ������ - ��� � ������ ������, ���� ��������� - ������ ������
	*/
	class GeneralMove : public SpecialMove
	{
		const sf::Vector2i& m_new_pos;
	public:
		void complete();
		GeneralMove(LogicBoard * board, Figure * moving_figure, const sf::Vector2i& new_pos);
	};


	// �������������� ����� � �����
	class PawnTransformMove : public SpecialMove
	{
		const sf::Vector2i& m_new_pos;
		SpecialMove * m_addition_move;
	public:
		void complete();
		PawnTransformMove(LogicBoard *, SpecialMove *, Figure * , const sf::Vector2i& new_pos);
		~PawnTransformMove(){delete m_addition_move;}
	};


	// ���������
	class CastlingMove : public SpecialMove
	{
		const sf::Vector2i  m_king_new_pos, m_rook_new_pos;
		Figure * m_ally_rook;
	public:
		void complete();
		CastlingMove(LogicBoard * board, Figure * const king, const sf::Vector2i& king_pos, Figure * const rook, const sf::Vector2i& rook_pos);
	};


}
