#include "stdafx.h"
#include "ui-element.h"

using namespace Graphics;

Label::Label(const std::string& text)
{
	m_text.setString(text);
}

void Label::draw(Graphics::Window& window)
{
	window.draw(*this);
	window.draw(m_text);
}

void Label::build()
{
	m_text.setFont(*m_font);
	m_text.setCharacterSize(m_charsize);
}