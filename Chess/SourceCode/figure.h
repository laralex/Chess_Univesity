#pragma once

#include "visual-block.h"

namespace Game
{
	class LogicBoard;
	class SpecialMove;

	enum FigureColor {
		Null=-1, White = 0, Black = 1
	};

	// БАЗОВЫЙ КЛАСС ФИГУР
	class Figure : protected Graphics::VisualBlock
	{
		friend class LogicBoard;
	protected:
		// Позиция на поле
		sf::Vector2i m_pos;
		// Цвет фигуры
		FigureColor m_color;
		// Привязка к конкретной доске
		LogicBoard * m_board;

		// Конструктор 
		Figure() : VisualBlock()
		{ }
	public:
		// Деструктор
		virtual ~Figure() {};
		
		// Возможность копирования
		Figure(const Figure& rhs);
		Figure& operator= (const Figure& rhs);

		// Отрисовка
		void draw(Graphics::Window& window);

		// Фигура должна сформировать ход в виде наследника интерфейса SpecialMove
		virtual bool createMove(SpecialMove ** move, const sf::Vector2i& new_pos) = 0;

		// Настройка параметров
		void setTexture(const sf::Texture * texture) { VisualBlock::setTexture(texture); }
		void setTextureRect(const sf::IntRect& rect) { VisualBlock::setTextureRect(rect); }
		void setColor(FigureColor color) { m_color = color; }
		void setBoard(LogicBoard* board) { m_board = board; }
		void setBoardPosition(const sf::Vector2i& new_pos) { m_pos = new_pos; }
		void setVisualPosition(const sf::Vector2f& pos) { VisualBlock::setPosition(pos); }
		void setVisualSize(const sf::Vector2f& size) { VisualBlock::setSize(size); }

		// Доступ к значениям
		sf::Vector2i getBoardPosition() const { return m_pos; }
		FigureColor  getColor() const { return m_color; }
		bool		 isWhite() const { return m_color == 0; }
		bool		 isNull() const { return m_color == -1; }
	};
}
