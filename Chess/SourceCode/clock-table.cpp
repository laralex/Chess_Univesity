#include "stdafx.h"
#include "clock-table.h"
#include "utils-functions.h"

using namespace Game;
using namespace Utils;

ClockTab::ClockTab(uint start_min, uint start_sec)
	: m_clock(start_min, start_sec)
{

}

void ClockTab::setPlayerName(const std::string& name)
{
	m_player_name.setString(name);
}

void Game::ClockTab::setFontColor(const sf::Color & color)
{
	m_player_name.setFillColor(color);
}

void ClockTab::draw(Graphics::Window& window)
{
	window.draw(*this);
	window.draw(m_player_name);
	window.draw(m_clock_text);
}

void  ClockTab::setIsActive(bool is_active)
{
	m_is_active = is_active;
	if (m_is_active)
		setOutlineThickness(5);
	else
		setOutlineThickness(0);
}		

bool ClockTab::tick() 
{ 
	if (m_clock.tick_one_sec())
	{
		m_clock_text.setString(m_clock.formString());
		return true;
	}
	return false;
}

void ClockTab::reset()
{
	m_clock_text.setString(m_clock.formString());
}


void ClockTab::build()
{
	sf::Vector2f my_pos = getPosition();

	applyFont();

	m_player_name.setPosition(my_pos.x + 5, my_pos.y + getHeight()/4 );
	m_player_name.setOutlineThickness(1);
	m_player_name.setOutlineColor(sf::Color(0,0,0));

	m_clock_text.setPosition(m_player_name.findCharacterPos(-1).x + 30, my_pos.y + getHeight()/4);
	m_clock_text.setString(m_clock.formString());
	m_clock_text.setFillColor(sf::Color(0, 0, 0));
}

void ClockTab::applyFont()
{
	m_player_name.setFont(*m_font);
	m_player_name.setCharacterSize(m_charsize);
	m_clock_text.setFont(*m_font);
	m_clock_text.setCharacterSize(m_charsize);
}

ClockTable::ClockTable(const sf::Vector2f& pos, const sf::Vector2f& size)
: VisualBlock(pos.x,pos.y,size.x,size.y)
{
	
}


void ClockTable::draw(Graphics::Window& window)
{
	window.draw(*this);
	m_white_clock.draw(window);
	m_black_clock.draw(window);
}

bool ClockTable::tick()
{
	if (m_is_current_turn_white)
		return m_white_clock.tick();
	else
		return m_black_clock.tick();
	return true;
}

void ClockTable::reset()
{
	setAllClocks(m_init_min, m_init_sec);
	m_sf_clock.restart();
	m_black_clock.reset();
	m_white_clock.reset();
	m_white_clock.setIsActive(true);
}

bool ClockTable::update()
{
	if (m_sf_clock.getElapsedTime().asSeconds() > 1)
	{
		m_sf_clock.restart();
		if (m_is_current_turn_white)
			return m_white_clock.tick();
		else
			return m_black_clock.tick();
	}
	return true;
}

void ClockTable::switchPlayerIfMoveMade(bool is_white_turn)
{
	if (is_white_turn != m_is_current_turn_white)
	{
		m_is_current_turn_white = is_white_turn;
		if (is_white_turn)
		{
			m_white_clock.setIsActive(true);
			m_black_clock.setIsActive(false);
		}
		else
		{
			m_white_clock.setIsActive(false);
			m_black_clock.setIsActive(true);
		}
	}
}

void ClockTable::setAllClocks(uint min, uint sec)
{
	m_white_clock.m_clock.setClock(min, sec);
	m_black_clock.m_clock.setClock(min, sec);
}
void ClockTable::build()
{
	// Загружаем настройки
	if(!m_settings) throw std::logic_error("Null settings pointer");
	sf::Vector2f my_pos = VisualBlock::getPosition(), my_size = VisualBlock::getSize();
	sf::Color tab_bg = recognize_color(m_settings->getValue("Clock", "ClockTabBGColor")),
		tab_highlight = recognize_color(m_settings->getValue("Clock", "ClockHighlightColor"));
	m_charsize = recognize_int(m_settings->getValue("Clock", "CharSize"));
	m_clock_tab_height = recognize_float(m_settings->getValue("Clock", "ClockTabHeight"));
	m_clock_tab_padding = recognize_float(m_settings->getValue("Clock", "ClockTabPadding"));

	setFillColor(recognize_color(m_settings->getValue("Clock", "ClockTableBGColor")));
	
	m_init_min = recognize_int(m_settings->getValue("Clock", "DefaultTime"));
	m_init_sec = 0;
	this->reset();

	applyFont();

	// Детально настраиваем часы белых
	m_white_clock.setPosition(my_pos.x, my_pos.y + m_clock_tab_height + m_clock_tab_padding);
	m_white_clock.setSize(my_size.x, m_clock_tab_height);
	m_white_clock.setFillColor(tab_bg);
	m_white_clock.setPlayerName("White");
	m_white_clock.setFontColor(sf::Color(240,240,240));
	m_white_clock.setOutlineColor(tab_highlight);
	m_white_clock.build();

	// Детально настраиваем часы черных
	m_black_clock.setPosition(my_pos);
	m_black_clock.setSize(my_size.x, m_clock_tab_height);
	m_black_clock.setFillColor(tab_bg);
	m_black_clock.setPlayerName("Black");
	m_black_clock.setFontColor(sf::Color(0, 0, 0));
	m_black_clock.setOutlineColor(tab_highlight);
	m_black_clock.build();
}

void ClockTable::applyFont()
{
	m_white_clock.setCharacterSize(m_charsize);
	m_white_clock.setFont(m_font);
	m_black_clock.setCharacterSize(m_charsize);
	m_black_clock.setFont(m_font);
}
