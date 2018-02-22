#include "stdafx.h"
#include "menu.h"
#include "utils-functions.h"

using namespace Graphics;
using namespace Utils;


// Добавление пункта
void MenuBlock::addTab(const std::string& tab_name)
{
	++m_tabs_number;
	m_tabs.push_back(new MenuTab(tab_name));
}

void MenuBlock::operator+=(const std::string& tab_name)
{
	addTab(tab_name);
}

void MenuBlock::build()
{
	// Применение настроек к меню и к пунктам меню
	if(!m_settings) throw std::logic_error("Null settings pointer");
	m_active_color = recognize_color(m_settings->getValue("Menu","ActiveTabColor"));
	m_inactive_color = recognize_color(m_settings->getValue("Menu", "InactiveTabColor"));
	m_charsize = recognize_int(m_settings->getValue("Menu", "CharSize"));
	m_max_tab_height = recognize_int(m_settings->getValue("Menu", "TabHeight"));
	VisualBlock::setFillColor(recognize_color(m_settings->getValue("Menu", "BackgroundColor")));
	setActiveTab(-1);
	uint count = 0;
	m_actual_tab_height = getHeight() > m_tabs_number * m_max_tab_height
							? m_max_tab_height : static_cast<uint>(getHeight() / m_tabs_number);
	for (auto it = m_tabs.begin(); it != m_tabs.end(); ++it)
	{
		(*it)->setCharacterSize(m_charsize);
		(*it)->setFont(m_font);
		(*it)->applyFont();
		(*it)->setSize(getWidth(), static_cast<float>(m_actual_tab_height));
		(*it)->setPosition(this->getX(), this->getY() + count * m_actual_tab_height);
		(*it)->setTexture(&*m_tab_texture);
		++count;
	}
}

void MenuBlock::moveNextTab()
{
	if (++m_active_tab == m_tabs_number) m_active_tab = 0;
	m_tab_switched = true;
}

void MenuBlock::movePrevTab()
{
	if (--m_active_tab < 0) m_active_tab = m_tabs_number - 1;
	m_tab_switched = true;
}

void MenuBlock::setActiveTab(int tab_num)
{
	m_active_tab = tab_num;
	m_tab_switched = true;
}

void MenuBlock::setTabTexture(const std::string filepath) 
{ 
	if (!m_tab_texture->loadFromFile(filepath))
		throw exceptions::file_not_open("Tab texture");

}

void MenuBlock::setCommand(int tab_num, const Command* command)
{
	m_tabs[tab_num]->command = command;
}

void MenuBlock::draw(Graphics::Window& window)
{
	window.draw(*this);
	uint count = 0;
	for (auto it = m_tabs.begin(); it != m_tabs.end(); ++it)
	{
		if (m_tab_switched)
		{
			if (count == m_active_tab)
				(*it)->setColor(m_active_color);
			else
				(*it)->setColor(m_inactive_color);
		}
		(*it)->draw(window);
		count++;
	}
	m_tab_switched = false;
}

void MenuBlock::mouse_down(const sf::Vector2i& vec)
{
}

void MenuBlock::mouse_up(const sf::Vector2i& vec) 
{
	if(m_active_tab >= 0) m_tabs[m_active_tab]->execute();
}

void MenuBlock::dishover(const sf::Vector2i& vec)
{
	setActiveTab(-1);
}

void MenuBlock::hover(const sf::Vector2i& vec)
{
	setActiveTab((static_cast<uint>(vec.y - getY()) / m_actual_tab_height));
}

bool MenuBlock::needsToProcessMouse(const sf::Vector2i& vec)
{
	float x = getX(), y = getY();
	return vec.y < (y + m_tabs_number*m_actual_tab_height) &&
		   vec.y > y &&
		   vec.x > x && 
		   vec.x < (x + getWidth());
}
