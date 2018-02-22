#include "stdafx.h"
#include "logic-board.h"
#include "special-move.h"
#include "utils-functions.h"
#include "chess-board.h"

using namespace Game;
using namespace Utils;

// Белые сверху, черные снизу
const uint initState1[8][8] = {
	{ 2 , 3 , 4 , 5,  6 , 4,  3 , 2 },
	{ 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 },
	{ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
	{ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
	{ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
	{ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
	{ 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 },
	{ 10, 11, 12, 13, 14, 12, 11, 10 }
};
// Черные сверху, белые снизу
const uint initState2[8][8] = {
	{ 10, 11, 12, 13, 14, 12, 11, 10 },
	{ 9 , 9 , 9 , 9 , 9 , 9 , 9 , 9 },
	{ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
	{ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
	{ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
	{ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
	{ 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 },
	{ 2 , 3 , 4 , 5,  6 , 4,  3 , 2 }
};

LogicBoard::LogicBoard(SettingsPart * settings, const sf::Vector2f& cell_offset, float cell_size)
	: m_settings(settings), m_cell_size(cell_size), m_cell_offset(cell_offset), m_game_state(NotStarted)
{
	m_figures.resize(64);
}

uint LogicBoard::getFigureIndex(const sf::Vector2i& board_position) const
{
	return board_position.x + 8 * board_position.y;
}

uint LogicBoard::getFigureIndex(const Figure * figure) const
{
	return getFigureIndex(figure->getBoardPosition());
}

Figure * LogicBoard::getFigure(const sf::Vector2i& board_position) const
{
	return m_figures.at(getFigureIndex(board_position));
}

Figure * LogicBoard::getFigure(const uint index) const
{
	return m_figures.at(index);
}


Figure * LogicBoard::getFigure(uint x, uint y) const
{
	return getFigure(sf::Vector2i(x,y));
}


void LogicBoard::build()
{
	// Создаем фабрику
	m_factory = new FigureFactory();
	m_factory->setLogicBoard(this);
	m_factory->setWhiteOffset(0);
	m_factory->setOneTileSize(sf::Vector2i(
		recognize_int(m_settings->getValue("Figures", "FigureTexture_W")),
		recognize_int(m_settings->getValue("Figures", "FigureTexture_H"))));
	m_factory->setTextureTileSize(sf::Vector2i(
		recognize_int(m_settings->getValue("Figures", "FiguresTile_W")),
		recognize_int(m_settings->getValue("Figures", "FiguresTile_H"))));
	sf::Texture * figuresTile = new sf::Texture;
	figuresTile->loadFromFile(m_settings->getValue("Figures", "FiguresTexture"));
	m_factory->setTextureTile(figuresTile);
}

void LogicBoard::resetFigures()
{
	// В соответствии с массивом кодов, воссоздаем доску
	m_is_white_move = true;
	m_figures.clear();
	m_figures.resize(64);
	auto init_array = m_is_white_at_bottom ? initState2 : initState1;
	Figure * createdFigure;
	for (int x = 0; x < 8; ++x)
	{
		for (int y = 0; y < 8; ++y)
		{
			createdFigure = m_factory->createFigure(init_array[y][x], sf::Vector2i(x, y));
			initVisualState(createdFigure);
			m_figures[y * 8 + x] = createdFigure;
		}
	}
}

void LogicBoard::swapFigures(uint index1, uint index2)
{
	// Меняем местами фигуры визуально
	Figure ** p_fig1 = &m_figures[index1], ** p_fig2 = &m_figures[index2];
	sf::Vector2i tmp_pos = (*p_fig1)->getBoardPosition();
	(*p_fig1)->setBoardPosition((*p_fig2)->getBoardPosition());
	(*p_fig2)->setBoardPosition(tmp_pos);
	updateVisualState(*p_fig1);
	updateVisualState(*p_fig2);
	// Меняем местами в массиве логически
	Figure * tmp = *p_fig1;
	*p_fig1 = *p_fig2;
	*p_fig2 = tmp;
}

void LogicBoard::swapFigures(Figure * fig1, Figure * fig2)
{
	swapFigures(getFigureIndex(fig1), getFigureIndex(fig2));
}

void LogicBoard::end()
{
	m_game_state = Over;
}

bool LogicBoard::isUnrealMove(const Figure * const figure, const sf::Vector2i& dest_pos)
{
	return m_game_state == Over || // Игра завершена
		figure->isNull() || // Фигура пустая 
		figure->getColor() != (m_is_white_move ? FigureColor::White : FigureColor::Black) || // Чужой ход
		!isInBoardRange(dest_pos) || // Ход все доски
		figure->getColor() == getFigure(dest_pos)->getColor(); // Ход в клетку союзника
}
bool LogicBoard::moveFigure(Figure * const figure, const sf::Vector2i& dest_pos){
	// Первичная проверка корректности
	if (isUnrealMove(figure, dest_pos)) return false;
	SpecialMove * move = 0;
	// Фигура генерирует ход (заодно проверяет ход по своим правилам)
	figure->createMove(&move, dest_pos);
	if (!move) return false; // Ход не создан
	move->complete(); // Доска совершает ход
	delete move;
	m_is_white_move ^= 1; // Смена хода
	return true;
}

void LogicBoard::updateVisualState(Figure* figure)
{
	// Отрисовать фигуру там, где она на доске
	figure->setVisualPosition(
		m_cell_offset +
		static_cast<sf::Vector2f>(figure->getBoardPosition()) * m_cell_size);
}

void LogicBoard::initVisualState(Figure* figure)
{
	// Инициализировать размер и положение
	updateVisualState(figure);
	figure->setVisualSize(sf::Vector2f(m_cell_size, m_cell_size));
}

bool LogicBoard::isInBoardRange(const sf::Vector2i& position)
{
	// В рамках доски
	return position.x >= 0 && position.y >= 0 && position.x <= 8 && position.y <= 8;
}

void LogicBoard::setFigureSpritePosition(Figure * fig, sf::Vector2f pos)
{
	fig->setPosition(pos);
}

bool LogicBoard::isNonEmptyCell(const sf::Vector2i& position) const
{
	return !m_figures[getFigureIndex(position)]->isNull();
}

bool LogicBoard::isNonEmptyCell(const uint index) const
{
	return dynamic_cast<NullFigure*>(m_figures[index]) == 0;
}

void LogicBoard::captureFigure(const sf::Vector2i& position)
{
	Figure ** new_figure = &m_figures[getFigureIndex(position)];
	delete *new_figure;
	*new_figure = m_factory->createFigure(0, position);
	initVisualState(*new_figure);
}

Figure * LogicBoard::transformPawn(Figure * pawn)
{
	//Преобразуем пешку
	Figure * new_figure;
	int color_bit = pawn->isWhite() ? 0 : 8;
	sf::Vector2i pos = pawn->getBoardPosition();
	delete pawn;
	new_figure = m_factory->createFigure(color_bit + 5, pos);
	initVisualState(new_figure);
	m_figures[getFigureIndex(pos)] = new_figure;
	return new_figure;
}
