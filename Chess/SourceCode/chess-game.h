#pragma once

#include "window.h"
#include "parser-ini.h"
#include "menu.h"
#include "mouse-controller.h"
#include "chess-board.h"
#include "clock-table.h"
#include "text-message.h"

// Главный класс игры

class ChessGame
{
	friend class PlayMenuCommand; // Команды меню могут влиять на класс
private:

	// Настройки игры из ini файла
	Utils::ParserIni& m_settings;

	// Обработчик мышки
	Utils::MouseController * m_mouse_controller;

	// Основное окно игры
	Graphics::Window m_window;

	// Меню
	Graphics::MenuBlock * m_main_menu;

	// Шрифт для текста игры
	sf::Font * m_main_font;

	// Настройки визуальных элементов
	sf::Vector2f WIN_SIZE, MENU_POS, MENU_SIZE, CLOCK_POS, CLOCK_SIZE, MSGBOX_SIZE, MSGBOX_POS;

	// Игровые объекты
	Game::ChessBoard * m_board; // Доска
	Game::ClockTable * m_clock_table; // Часы
	TextMessage * m_message_box;

	// Идет ли игра
	bool m_is_game_in_process = false;

	// Создание и копирование игры запрещено (Синглтон)
	ChessGame()
		: m_settings(Utils::ParserIni::getInstance()), m_main_font() {}
	ChessGame(const ChessGame&) = delete;
	ChessGame& operator=(const ChessGame&) = delete;

	// Инициализация объектов, загрузка настроек
	void initGame();
	void initMouseController();
	void initClocks();
	void initMenu();
	void initBoard();
	void initTextMessage();

	// Запуск бесконечного цикла графики SFML и самой игры 
	void start_SFML_Loop();
	// Закончить игру принудительно 
	void endGame(bool isWhiteWinner);

public:
	// Получить объект(синглтон) игры
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