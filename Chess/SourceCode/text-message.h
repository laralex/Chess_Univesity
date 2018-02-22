#pragma once

#include "visual-block.h"
#include "textable.h"
#include "settings-part.h"

class TextMessage : public Graphics::VisualBlock, public Textable
{
protected:
	std::vector<sf::Text> m_text;
	Utils::SettingsPart * m_settings;
public:
	TextMessage(const sf::Vector2f& pos, const sf::Vector2f& size)
		: VisualBlock(pos.x, pos.y, size.x, size.y), m_text(4)
	{

	}
	~TextMessage()
	{
		delete m_settings;
	}
	void setText(const std::vector<std::string>& text);
	void setTextColor(const sf::Color color);
	void clearText();
	void setSettings(Utils::SettingsPart * settings) { m_settings = settings; }
	void build();
	void applyFont();
	void draw(Graphics::Window& window);
};

class WinMessage : TextMessage
{
public:

};
