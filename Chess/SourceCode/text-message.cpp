#include "stdafx.h"
#include "text-message.h"
#include "utils-functions.h"

using namespace Utils;

void TextMessage::applyFont()
{
	for (auto& line : m_text)
	{
		line.setFont(*m_font);
		line.setCharacterSize(m_charsize);
	}
	
}

void TextMessage::build()
{
	setFillColor(recognize_color(m_settings->getValue("TextMessage", "BackgroundColor")));
	m_charsize = recognize_int(m_settings->getValue("TextMessage", "CharSize"));
	uint counter = 0;
	for (auto& line : m_text)
	{
		line.setOutlineThickness(1);
		line.setOutlineColor(sf::Color(0, 0, 0));
		line.setPosition(getX(), getY() + m_charsize*(counter++));
	}
	applyFont();
}

void TextMessage::setText(const std::vector<std::string>& text)
{
	uint counter = 0;
	auto it = m_text.begin();
	for (auto& line : text)
	{
		it->setString(line);
		it->setPosition(getX() + (getWidth() - it->getLocalBounds().width)*0.5f, getY() + m_charsize*(counter++));
		++it;
	}
}

void TextMessage::clearText()
{
	for (auto& line : m_text)
	{
		line.setString("");
	}
}

void TextMessage::setTextColor(const sf::Color color)
{
	for (auto& line : m_text)
	{
		line.setFillColor(color);
	}
}

void TextMessage::draw(Graphics::Window& window)
{
	window.draw(*this);
	for (auto& line : m_text)
	{
		window.draw(line);
	}
}