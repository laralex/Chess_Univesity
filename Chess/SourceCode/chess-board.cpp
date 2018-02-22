#include "stdafx.h"
#include "chess-board.h"
#include "logic-board.h"

using namespace Game;
using namespace Utils;

ChessBoard::~ChessBoard()
{
	delete m_settings;
	delete m_logic_board;
}

void ChessBoard::loadSettings()
{
	// Настраиваем
	if (!m_settings) throw std::logic_error("Null settings pointer");
	m_white_color = recognize_color(m_settings->getValue("Board", "CellWhiteColor"));
	m_black_color = recognize_color(m_settings->getValue("Board", "CellBlackColor"));
	m_use_frame = recognize_bool(m_settings->getValue("Board", "UseFrame"));
	if (m_use_frame)
	{
		m_frame_color = recognize_color(m_settings->getValue("Board", "FrameColor"));
		m_frame_size = recognize_float(m_settings->getValue("Board", "FrameWidth"));
	}
}

void ChessBoard::initLogicBoard()
{
	// Создаем логическую часть доски
	if (!m_settings) throw std::logic_error("Null settings pointer");
	if (!m_logic_board) delete m_logic_board;
	m_logic_board = new LogicBoard(m_settings, m_cell_offset, m_cell_size);
	m_logic_board->setWhiteSideDown(true);
	m_logic_board->build();
}

void ChessBoard::build()
{
	// Применяем настройки
	loadSettings();
	// Создаем визуальную часть
	bool colorswitch = true;
	sf::Vector2f offset(VisualBlock::getPosition());
	// Образуем рамку
	if (m_use_frame)
	{
		m_frame_rect.setFillColor(m_frame_color);
		m_frame_rect.setSize(sf::Vector2f(m_size, m_size));
		m_frame_rect.setPosition(offset);
		m_cell_size = (m_size-2*m_frame_size)/8.f; 
		offset.x += m_frame_size;
		offset.y += m_frame_size;
	}
	else
		m_cell_size = m_size/8.f;

	// Образуем клетчатое поле
	sf::Vertex* quad;
	for (int i = 0; i < 8; ++i)
	{
		for (int j = 0; j < 8; ++j)
		{
			quad = &m_board_vertices[(i + j * 8) * 4];
			quad[0].position = offset + sf::Vector2f(i * m_cell_size, j * m_cell_size);
			quad[1].position = offset + sf::Vector2f((i + 1) * m_cell_size, j * m_cell_size);
			quad[2].position = offset + sf::Vector2f((i + 1) * m_cell_size, (j + 1) * m_cell_size);
			quad[3].position = offset + sf::Vector2f(i * m_cell_size, (j + 1) * m_cell_size);
			quad[0].color = quad[1].color = quad[2].color = quad[3].color
				= colorswitch ? m_white_color : m_black_color;
			colorswitch ^= 1;
		}
		colorswitch ^= 1;
	}
	m_cell_offset = offset;
	// Создаем логическую часть
	initLogicBoard();
}

void ChessBoard::draw(Graphics::Window& window)
{
	// Рисуем себя, рамку, клетки, фигуры
	window.draw(*this);
	window.draw(m_frame_rect);
	window.draw(m_board_vertices);
	Figure * figure = 0;
	for (int i = 0; i < 64; ++i)
	{
		figure = m_logic_board->getFigure(i);
		if(figure != m_draging_figure)	
			figure->draw(window);
	}
	// Ту фигуру, которую тащит пользователь поверх всего
	if (m_draging_figure)
	{
		m_draging_figure->draw(window);
	}
}

void ChessBoard::start()
{
	m_logic_board->resetFigures();
	m_logic_board->m_game_state = Playing;
}

void ChessBoard::end()
{
	m_logic_board->m_game_state = Over;
}

bool ChessBoard::isMoveOfWhite()
{
	return m_logic_board->m_is_white_move;
}

GameState ChessBoard::getGameState()
{
	return m_logic_board->m_game_state;
}

sf::Vector2i ChessBoard::convertGlobalToBoardCoords(const sf::Vector2i& global_position)
{
	sf::Vector2i board_coords(static_cast<int>((global_position.x - m_cell_offset.x) / m_cell_size),
							  static_cast<int>((global_position.y - m_cell_offset.y) / m_cell_size));
	if (board_coords.x > 7 || board_coords.y > 7) return sf::Vector2i(-1, -1);
	return board_coords;
}

// Проверяет равенство позиций фигур
bool equalFiguresPos(const Figure * fig1, const Figure * fig2)
{
	return fig1->getBoardPosition() == fig2->getBoardPosition();
}

void ChessBoard::mouse_down(const sf::Vector2i& vec)
{
	// Если переносим фигуру
	if (m_draging_figure)
	{
		// То фигура рисуется рядом с курсором
		m_logic_board->setFigureSpritePosition
			(m_draging_figure,
			sf::Vector2f(vec) - sf::Vector2f(m_cell_size, m_cell_size)*0.5f);
		return;
	}
	// Иначе начинаем перетаскивать фигуру с доски 
	sf::Vector2i board_click 
		= convertGlobalToBoardCoords(vec);
	if (m_logic_board->isInBoardRange(board_click))
		m_draging_figure = m_logic_board->getFigure(board_click);
}
void ChessBoard::mouse_up(const sf::Vector2i& vec)
{
	sf::Vector2i board_release_position
		= convertGlobalToBoardCoords(vec);
	// Если	перетаскивали фигуру
	if (m_draging_figure)
		// То пытаемся походить ей
		if (!m_logic_board->moveFigure(m_draging_figure, board_release_position))
			// Если не получилось, возвращаем на место
			m_logic_board->updateVisualState(m_draging_figure);
	m_draging_figure = 0;
}

void ChessBoard::hover(const sf::Vector2i& vec)
{
   // Наведение курсора нас не доску не интерисует
}

void ChessBoard::dishover(const sf::Vector2i& vec)
{
	// При покидании доски мы отпускаем фигуру
	if (m_draging_figure) 
		m_logic_board->updateVisualState(m_draging_figure);
	m_draging_figure = 0;
}

bool ChessBoard::needsToProcessMouse(const sf::Vector2i& vec)
{
	// Если курсор в рамках доски, то нам нужно обработать мышку
	float x = VisualBlock::getX(), y = VisualBlock::getY();
	if (vec.x >= x && vec.y >= y &&
		vec.x <= x + m_size && vec.y <= y + m_size)
		return true;
	return false;
}