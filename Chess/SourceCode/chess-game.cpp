
#include "stdafx.h"
#include "chess-game.h"
#include "menu-commands.h"
#include "concrete-settings.h"
#include "settings-part.h"

using namespace std;
using namespace Utils;
using namespace Game;

// Состояние игры

void ChessGame::launch()
{
	initGame();
}

void ChessGame::initMenu()
{
	// Создаем меню	и настраиваем
	m_main_menu = new Graphics::MenuBlock(MENU_POS, MENU_SIZE);

	SettingsPart * menu_settings = new SettingsPart(1);
	*menu_settings += m_settings.getSection("Menu");

	m_main_menu->setSettings(menu_settings);

	// Текстура кнопки
	shared_ptr<sf::Texture> button_texture(new sf::Texture());
	if (!button_texture->loadFromFile(m_settings["Resources"]["ButtonTexture"]))
		throw exceptions::file_not_open("Button texture");
	m_main_menu->setTabTexture(button_texture);

	m_main_menu->setFont(m_main_font);
	m_main_menu->setCharacterSize(35);

	// Добавляем кнопки
	*m_main_menu += "Play";
	PlayMenuCommand* startCommand = new PlayMenuCommand(*this);
	m_main_menu->setCommand(0, startCommand);

	*m_main_menu += "Quit";
	ExitMenuCommand* exitCommand = new ExitMenuCommand(*this);
	m_main_menu->setCommand(1, exitCommand);

	// Собираем воедино меню
	m_main_menu->build();
}

void ChessGame::initBoard()
{
	// Создаем доску и настраиваем
	SettingsPart * board_settings = new SettingsPart(2);
	*board_settings += m_settings.getSection("Board");
	*board_settings += m_settings.getSection("Figures");

	m_board = new Game::ChessBoard(board_settings);

	m_board->setSize(static_cast<float>(WIN_SIZE.y));

	m_board->build();
}

void ChessGame::initClocks()
{
	// Создаем таймер и настраиваем
	SettingsPart * clocks_settings = new SettingsPart(2);
	*clocks_settings += m_settings.getSection("Clock");
	*clocks_settings += m_settings.getSection("Resources");
	m_clock_table = new Game::ClockTable(CLOCK_POS, CLOCK_SIZE);
	m_clock_table->setSettings(clocks_settings);
	m_clock_table->setFont(m_main_font);
	m_clock_table->build();
}

void ChessGame::initMouseController()
{
	// Создаем обработчик мыши и передаем элементы, которые взаимодействуют с мышью
	m_mouse_controller = new Utils::MouseController(m_window);
	m_mouse_controller->addObserver(m_main_menu);
	m_mouse_controller->addObserver(m_board);
}

void ChessGame::initTextMessage()
{
	SettingsPart * settings = new SettingsPart(1);
	*settings += m_settings.getSection("TextMessage");
	m_message_box = new TextMessage(MSGBOX_POS, MSGBOX_SIZE);
	//m_message_box->setText("DO IT");
	m_message_box->setSettings(settings);
	m_message_box->setFont(m_main_font);
	m_message_box->build();
}

void ChessGame::initGame()
{
	// Инициализация все что можно
	m_settings.parse(string("./Resources/config.ini"));
	WIN_SIZE.x = recognize_float(m_settings["Window"]["Width"]);
	WIN_SIZE.y = recognize_float(m_settings["Window"]["Height"]);
	m_main_font = new sf::Font;
	if (!m_main_font->loadFromFile(m_settings["Resources"]["FontFile"]))
		throw exceptions::file_not_open("Main font");
	m_window.create((uint)WIN_SIZE.x, (uint)WIN_SIZE.y, m_settings["Window"]["Title"]);
	MENU_SIZE = { WIN_SIZE.x - WIN_SIZE.y, WIN_SIZE.y / 3};
	MENU_POS = { WIN_SIZE.x - MENU_SIZE.x , 0};
	CLOCK_SIZE = MENU_SIZE;
	CLOCK_POS = { WIN_SIZE.x - MENU_SIZE.x, WIN_SIZE.y / 3 };
	MSGBOX_POS = { WIN_SIZE.x - MENU_SIZE.x, WIN_SIZE.y * 2 / 3 };
	MSGBOX_SIZE = MENU_SIZE;
	initMenu();
	initBoard();
	initClocks();
	initMouseController();
	initTextMessage();
	start_SFML_Loop();
}

void ChessGame::endGame(bool isWhiteWinner)
{
	m_is_game_in_process = false;
	if (isWhiteWinner)
	{
		const char * text[] = { "White" , "has", "won" };
		m_message_box->setText(std::vector<std::string>(text, text + 3));
		m_message_box->setTextColor(sf::Color(255, 255, 255));
	}
	else
	{
		const char * text[] = { "Black" , "has", "won" };
		m_message_box->setText(std::vector<std::string>(text, text + 3));
		m_message_box->setTextColor(sf::Color(0, 0, 0));
	}
	m_board->end();
}

void ChessGame::restartGame()
{
	m_board->start();
	m_message_box->clearText();
	m_is_game_in_process = true;
	m_clock_table->reset();
}

void ChessGame::exit()
{
	m_window.close();
}

void ChessGame::start_SFML_Loop()
{
	// Основной цикл SFML
	sf::Event event;
	while (m_window.isOpen())
	{
		while (m_window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				m_window.close();
			m_mouse_controller->processMouseEvents(event);
		}
		switch (m_board->getGameState())
		{
		case GameState::Playing:
			m_clock_table->switchPlayerIfMoveMade(m_board->isMoveOfWhite());
			if (!m_clock_table->update()) endGame(!m_board->isMoveOfWhite());
			break;
		case GameState::Over:
			endGame(!m_board->isMoveOfWhite());
			break;
		}

		m_window.clear();
		m_board->draw(m_window);
		m_main_menu->draw(m_window);
		m_clock_table->draw(m_window);
		m_message_box->draw(m_window);
		m_window.display();
	}
}

