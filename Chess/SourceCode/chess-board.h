#pragma once

#include "visual-block.h"
#include "mouse-behaviour.h"
#include "figure-factory.h"
#include "settings-part.h"


namespace Game
{
	class LogicBoard;
	
	// ��������� ����
	enum GameState
	{
		NotStarted, Playing, Check, Over, Pause
	};

	// ��������� �����
	class ChessBoard : public Graphics::VisualBlock, public MouseBehaviour
	{
	private:
		// ��������� �����
		Utils::SettingsPart * m_settings;
		// ������ opengl �����, ��� ����������� ������
		sf::VertexArray m_board_vertices;
		// ������� �����
		sf::RectangleShape m_frame_rect;
	
		// ������ ����� (� ��������), ������ �����, ������� ����� ������
		float m_size, m_frame_size, m_cell_size;
		// ������������ �� ����� ��� ���������
		bool m_use_frame;
		// ����� ������ ������������ �����
		sf::Vector2f m_cell_offset;

		// �����: ����� � ������ ������, �����
		sf::Color m_white_color, m_black_color, m_frame_color;

		// ���������� ����� - ������������� ��������� ������
		Game::LogicBoard * m_logic_board;

		// ������, ������� ����� ������ ������������
		Game::Figure * m_draging_figure;

		// ������� ����� - ������������� �������� �����
		Game::FigureFactory * m_figure_factory;


		// ------------   Methods --------------------
		// ������������ ��� ������ � ��������� ���������
		void loadSettings();
		// ������������� ������� �����
		void initLogicBoard();
		// �������������� ���������� ���������� � ���������� ����� <x=0..7, y=0..7>
		sf::Vector2i convertGlobalToBoardCoords(const sf::Vector2i& global_coords);
	public:
		// ctor & dtor
		ChessBoard(Utils::SettingsPart * settings) 
			: m_settings(settings), m_board_vertices(sf::Quads, 64 * 4) 
		{

		}

		~ChessBoard();

		// ���������
		void draw(Graphics::Window&);

		// ��������� � ������
		void setSize(float size) { m_size = size; }
		void build();
		
		// ��� �� �����
		bool isMoveOfWhite();
		Game::GameState getGameState();

		// ������ ����
		void start();
		void end();

		// ��������� �������� �����
		void mouse_down(const sf::Vector2i& vec);
		void mouse_up(const sf::Vector2i& vec);
		void hover(const sf::Vector2i& vec);
		void dishover(const sf::Vector2i& vec);
		bool needsToProcessMouse(const sf::Vector2i& vec);		
	};
}