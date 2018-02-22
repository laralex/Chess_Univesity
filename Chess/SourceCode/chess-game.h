#pragma once

#include "window.h"
#include "parser-ini.h"
#include "menu.h"
#include "mouse-controller.h"
#include "chess-board.h"
#include "clock-table.h"
#include "text-message.h"

// ������� ����� ����

class ChessGame
{
	friend class PlayMenuCommand; // ������� ���� ����� ������ �� �����
private:

	// ��������� ���� �� ini �����
	Utils::ParserIni& m_settings;

	// ���������� �����
	Utils::MouseController * m_mouse_controller;

	// �������� ���� ����
	Graphics::Window m_window;

	// ����
	Graphics::MenuBlock * m_main_menu;

	// ����� ��� ������ ����
	sf::Font * m_main_font;

	// ��������� ���������� ���������
	sf::Vector2f WIN_SIZE, MENU_POS, MENU_SIZE, CLOCK_POS, CLOCK_SIZE, MSGBOX_SIZE, MSGBOX_POS;

	// ������� �������
	Game::ChessBoard * m_board; // �����
	Game::ClockTable * m_clock_table; // ����
	TextMessage * m_message_box;

	// ���� �� ����
	bool m_is_game_in_process = false;

	// �������� � ����������� ���� ��������� (��������)
	ChessGame()
		: m_settings(Utils::ParserIni::getInstance()), m_main_font() {}
	ChessGame(const ChessGame&) = delete;
	ChessGame& operator=(const ChessGame&) = delete;

	// ������������� ��������, �������� ��������
	void initGame();
	void initMouseController();
	void initClocks();
	void initMenu();
	void initBoard();
	void initTextMessage();

	// ������ ������������ ����� ������� SFML � ����� ���� 
	void start_SFML_Loop();
	// ��������� ���� ������������� 
	void endGame(bool isWhiteWinner);

public:
	// �������� ������(��������) ����
	static ChessGame& getInstance() 
	{
		
		static ChessGame singleton;
		return singleton;
	}
	~ChessGame()
	{
		delete m_main_menu;
		delete m_mouse_controller;
		delete m_board;
		delete m_clock_table;
		delete m_main_font;
	}
	void launch(); // init + start new game
	void restartGame(); // start new game
	void exit(); // exit the game
};