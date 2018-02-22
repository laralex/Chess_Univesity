#pragma once

#include "stdafx.h"

// ���������� ������ ��������, ������� ����� ��������� �����

class Textable
{
protected:
	// ������ ������
	const sf::Font * m_font;
	// ������ ������
	size_t m_charsize;
	Textable() {};
	Textable(const sf::Font * const font) { m_font = font; }
public:
	// ������ ������
	virtual void setCharacterSize(const size_t size) { m_charsize = size; };
	// �����
	virtual void setFont(const sf::Font * const font) { m_font = font; };
	// ��������� ������� ��������� ������
	virtual void applyFont() = 0;
};