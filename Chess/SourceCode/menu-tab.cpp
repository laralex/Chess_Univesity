
#include "stdafx.h"
#include "menu-tab.h"

using namespace Graphics;

void MenuTab::setPosition(float x, float y)
{
	VisualBlock::setPosition(x,y);
	m_text.setPosition(x + (VisualBlock::getWidth() - m_text.getLocalBounds().width)*0.5f, y);
}

void MenuTab::setPosition(const sf::Vector2f& new_pos)
{
	setPosition(new_pos.x, new_pos.y);
}


void MenuTab::applyFont()
{
	m_text.setFont(*m_font);
	m_text.setCharacterSize(m_charsize);
}

void MenuTab::draw(Graphics::Window& window)	
{
	window.draw(*this);
	window.draw(m_text);
}