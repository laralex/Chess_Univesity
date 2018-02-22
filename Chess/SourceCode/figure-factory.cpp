
#include "stdafx.h"
#include "figure-factory.h"
#include "logic-board.h"

using namespace Game;

FigureFactory::FigureFactory()
{
	// Отступы в текстурном файле figures.png
	m_texture_offsets[0] = 5;
	m_texture_offsets[1] = 4;
	m_texture_offsets[2] = 3;
	m_texture_offsets[3] = 2;
	m_texture_offsets[4] = 1;
	m_texture_offsets[5] = 0;
}
Figure * FigureFactory::createFigure(int figureCode, const sf::Vector2i& initPosition) const
{
	// Вычленяем из кода цвет и тип фигуры
	uint type = figureCode & ~8;
	bool isWhite = (figureCode & 8) == 0;
	Figure * createdFigure = 0;

	// Создаем фигуру по конструктору
	switch (type)
	{
	case 0:
		createdFigure = new NullFigure();
		createdFigure->setColor(FigureColor::Null);
		createdFigure->setBoard(m_board);
		createdFigure->setBoardPosition(initPosition);
		return createdFigure;
		break;
	case 1: 
		createdFigure = new Pawn(initPosition.y == 1 ? 1 : -1); 
		break;
	case 2: 
		createdFigure = new Rook(); 
		break;
	case 3: 
		createdFigure = new Knight(); 
		break;
	case 4: 
		createdFigure = new Bishop(); 
		break;
	case 5: 
		createdFigure = new Queen(); 
		break;
	case 6: 
		createdFigure = new King(); 
		break;
	}
	// Связываем новоиспеченную фигуру с доской и текстурами
	createdFigure->setBoard(m_board);
	createdFigure->setBoardPosition(initPosition);
	createdFigure->setTexture(m_texture_tile);
	createdFigure->setColor(isWhite ? FigureColor::White : FigureColor::Black);
	createdFigure->setTextureRect(sf::IntRect((m_texture_offsets[type-1]) * m_one_tile_size.x, !isWhite * m_one_tile_size.y, m_one_tile_size.x,m_one_tile_size.y)); 
	return createdFigure;
}
