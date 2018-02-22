#pragma once

#include "visual-block.h"
#include "mouse-behaviour.h"
#include "figure-factory.h"
#include "settings-part.h"


namespace Game
{
	class LogicBoard;
	
	// Состояние игры
	enum GameState
	{
		NotStarted, Playing, Check, Over, Pause
	};

	// Шахматная доска
	class ChessBoard : public Graphics::VisualBlock, public MouseBehaviour
	{
	private:
		// Настройки доски
		Utils::SettingsPart * m_settings;
		// Массив opengl точек, для отображения клеток
		sf::VertexArray m_board_vertices;
		// Боковая рамка
		sf::RectangleShape m_frame_rect;
	
		// Размер доски (в пикселях), размер рамки, размеры одной клетки
		float m_size, m_frame_size, m_cell_size;
		// Использовать ли рамку при рисовании
		bool m_use_frame;
		// Сдвиг клеток относительно рамки
		sf::Vector2f m_cell_offset;

		// Цвета: белой и черной клеток, рамки
		sf::Color m_white_color, m_black_color, m_frame_color;

		// Логическая доска - инкапсулирует шахматную логику
		Game::LogicBoard * m_logic_board;

		// Фигура, которую тянет мышкой пользователь
		Game::Figure * m_draging_figure;

		// Фабрика фигур - инкапсулирует создание фигур
		Game::FigureFactory * m_figure_factory;


		// ------------   Methods --------------------
		// Восстановить все фигуры в начальное положение
		void loadSettings();
		// Инициализация фабрики фигур
		void initLogicBoard();
		// Конвертировать глобальные координаты в координаты доски <x=0..7, y=0..7>
		sf::Vector2i convertGlobalToBoardCoords(const sf::Vector2i& global_coords);
	public:
		// ctor & dtor
		ChessBoard(Utils::SettingsPart * settings) 
			: m_settings(settings), m_board_vertices(sf::Quads, 64 * 4) 
		{

		}

		~ChessBoard();

		// Отрисовка
		void draw(Graphics::Window&);

		// Настройка и сборка
		void setSize(float size) { m_size = size; }
		void build();
		
		// Ход ли белых
		bool isMoveOfWhite();
		Game::GameState getGameState();

		// Запуск игры
		void start();
		void end();

		// Обработка действий мышки
		void mouse_down(const sf::Vector2i& vec);
		void mouse_up(const sf::Vector2i& vec);
		void hover(const sf::Vector2i& vec);
		void dishover(const sf::Vector2i& vec);
		bool needsToProcessMouse(const sf::Vector2i& vec);		
	};
}