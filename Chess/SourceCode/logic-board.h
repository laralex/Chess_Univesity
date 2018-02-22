#pragma once

#include "figure-factory.h"
#include "settings-part.h"

namespace Game
{
	// Состояние игры
	enum GameState;/*
	{
		NotStarted, Playing, Check, Over, Pause
	};*/

	// Логическая доска - инкапсулирует шахматную логику
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

		// Получить по позиции на доске дает доступ к фигуре
		Figure * getFigure(uint x, uint y) const;
		Figure * getFigure(const uint index) const;
		Figure * getFigure(const sf::Vector2i& board_position) const;

	
		// Запрос на передвижение фигуры
		// return -> true - ход совершен, false - ход недопустим
		bool moveFigure(Figure * const figure, const sf::Vector2i& dest_pos);

		// Принадлежит ли позиция доске
		bool isInBoardRange(const sf::Vector2i& position);
		// Проверка абсурдности попытки хода
		bool isUnrealMove(const Figure * const figure, const sf::Vector2i& dest_pos);

		// Есть ли фигура в этой позиции
		bool isNonEmptyCell(const sf::Vector2i& position) const;
		bool isNonEmptyCell(const uint index) const;

		// Визуально отображает фигуру там, где она должна быть на доске
		void updateVisualState(Figure* figure);
		void initVisualState(Figure* figure);

		// Сборка доски
		void build();
		void end();
		// Установить положение белой стороны внизу доски 
		void setWhiteSideDown(bool is_white_at_bottom) { m_is_white_at_bottom = is_white_at_bottom; }

		// Удалить фигуру в этой позиции
		void captureFigure(const sf::Vector2i& position);
	private:
		// Сбросить позицию фигур до изначальной
		void resetFigures();
		// Получить позицию фигуры в массиве фигур
		uint getFigureIndex(const Figure * figure) const;
		uint getFigureIndex(const sf::Vector2i& board_position) const;
		// Установить визуальную позицию фигуры
		void setFigureSpritePosition(Figure * fig, sf::Vector2f pos);
		// Поменять фигуры местами
		void swapFigures(uint index1, uint index2);
		void swapFigures(Figure * fig1, Figure * fig2);
		// Превратить пешку в ферзя
		Figure * transformPawn(Figure * pawn);

		// ------------ Data ---------------------
		// Состояние игры
		GameState m_game_state;
		// Vector of figures 8x8
		std::vector<Game::Figure*> m_figures;
		// Фабрика будет создавать фигуры
		FigureFactory * m_factory;
		// Визуальный сдвиг левой верхней клетки
		sf::Vector2f m_cell_offset;
		// Настройки
		Utils::SettingsPart * m_settings;
		// Размер клетки
		float m_cell_size;
		// Находится ли белая сторона снизу
		bool m_is_white_at_bottom;
		// Ход ли белых
		bool m_is_white_move = true;
		
	};
}

