#include "stdafx.h"
#include "popup-message.h"

using namespace Graphics;

PopupMessage::~PopupMessage()
{
	for (auto it = m_content.begin(); it != m_content.end(); ++it)
		delete *it;
}
TextMessage::TextMessage(const std::string& text) 
{
	m_content.push_back(new Label(text));
}

void TextMessage::draw(Window& window)
{
	window.draw(*this);
	for (auto it = m_content.begin(); it != m_content.end(); ++it)
		(*it)->draw(window);
}