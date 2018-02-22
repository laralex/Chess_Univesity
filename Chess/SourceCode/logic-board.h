#pragma once

#include "figure-factory.h"
#include "settings-part.h"

namespace Game
{
	// ��������� ����
	enum GameState;/*
	{
		NotStarted, Playing, Check, Over, Pause
	};*/

	// ���������� ����� - ������������� ��������� ������
	class LogicBoard
	{
		friend class SpecialMove;
		friend class InEmptyCellMove;
		friend class PawnTransformMove;
		friend class ChessBoard;
	public:
		// ctor, dtor
		LogicBoard(Utils::SettingsPart * settings, const sf::Vector2f& cell_offset, float cell_size);
		~LogicBoard()
		{
			delete m_factory;
		}

		// �������� �� ������� �� ����� ���� ������ � ������
		Figure * getFigure(uint x, uint y) const;
		Figure * getFigure(const uint index) const;
		Figure * getFigure(const sf::Vector2i& board_position) const;

	
		// ������ �� ������������ ������
		// return -> true - ��� ��������, false - ��� ����������
		bool moveFigure(Figure * const figure, const sf::Vector2i& dest_pos);

		// ����������� �� ������� �����
		bool isInBoardRange(const sf::Vector2i& position);
		// �������� ����������� ������� ����
		bool isUnrealMove(const Figure * const figure, const sf::Vector2i& dest_pos);

		// ���� �� ������ � ���� �������
		bool isNonEmptyCell(const sf::Vector2i& position) const;
		bool isNonEmptyCell(const uint index) const;

		// ��������� ���������� ������ ���, ��� ��� ������ ���� �� �����
		void updateVisualState(Figure* figure);
		void initVisualState(Figure* figure);

		// ������ �����
		void build();
		void end();
		// ���������� ��������� ����� ������� ����� ����� 
		void setWhiteSideDown(bool is_white_at_bottom) { m_is_white_at_bottom = is_white_at_bottom; }

		// ������� ������ � ���� �������
		void captureFigure(const sf::Vector2i& position);
	private:
		// �������� ������� ����� �� �����������
		void resetFigures();
		// �������� ������� ������ � ������� �����
		uint getFigureIndex(const Figure * figure) const;
		uint getFigureIndex(const sf::Vector2i& board_position) const;
		// ���������� ���������� ������� ������
		void setFigureSpritePosition(Figure * fig, sf::Vector2f pos);
		// �������� ������ �������
		void swapFigures(uint index1, uint index2);
		void swapFigures(Figure * fig1, Figure * fig2);
		// ���������� ����� � �����
		Figure * transformPawn(Figure * pawn);

		// ------------ Data ---------------------
		// ��������� ����
		GameState m_game_state;
		// Vector of figures 8x8
		std::vector<Game::Figure*> m_figures;
		// ������� ����� ��������� ������
		FigureFactory * m_factory;
		// ���������� ����� ����� ������� ������
		sf::Vector2f m_cell_offset;
		// ���������
		Utils::SettingsPart * m_settings;
		// ������ ������
		float m_cell_size;
		// ��������� �� ����� ������� �����
		bool m_is_white_at_bottom;
		// ��� �� �����
		bool m_is_white_move = true;
		
	};
}

