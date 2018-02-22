#pragma once

#include "conctere-figures.h"

enum Type
{
	Pawn = 1, Rook, Knight, Bishop, Queen, King
};

enum Color
{
	White = 0, Black = 8
};
namespace Game
{
	class Game::LogicBoard;

	// Фабрика фигур - инкапсулирует создание фигур
	class FigureFactory
	{
		// Настройки, передаваемые фигурам
		LogicBoard * m_board;
		const sf::Texture * m_texture_tile;
		size_t m_white_offset;
		size_t m_texture_offsets[6];
		sf::Vector2i m_one_tile_size, m_full_tile_size;
		sf::Vector2f m_board_offset;
		float m_cell_size;
	public:
		// c-tor & d-tor
		FigureFactory();

		~FigureFactory()
		{ delete m_texture_tile; }

		// Создает фигуру по специальному ходу
		Figure * createFigure(int figureCode, const sf::Vector2i& initPosition = sf::Vector2i(0,0)) const;

		// Настройка фабрики извне
		void setLogicBoard(LogicBoard* board) { m_board = board; }
		void setTextureTile(const sf::Texture* texture) { m_texture_tile = texture; }
		void setOneTileSize(const sf::Vector2i& size) { m_one_tile_size = size; }
		void setTextureTileSize(const sf::Vector2i& size) { m_full_tile_size = size; }
		void setWhiteOffset(size_t offset = 0) { m_white_offset = offset;}
	};
}