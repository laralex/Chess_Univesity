#pragma once

#include "stdafx.h"

// Суперкласс любого элемента, который может содержать текст

class Textable
{
protected:
	// Объект шрифта
	const sf::Font * m_font;
	// Размер шрифта
	size_t m_charsize;
	Textable() {};
	Textable(const sf::Font * const font) { m_font = font; }
public:
	// Размер шрифта
	virtual void setCharacterSize(const size_t size) { m_charsize = size; };
	// Шрифт
	virtual void setFont(const sf::Font * const font) { m_font = font; };
	// Применить текущие параметры шрифта
	virtual void applyFont() = 0;
};