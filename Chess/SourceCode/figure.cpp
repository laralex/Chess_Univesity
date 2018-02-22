#include "stdafx.h"
#include "figure.h"

using namespace Game;

Figure::Figure(const Figure& rhs)
{
	this->m_board = rhs.m_board;
	this->m_color = rhs.m_color;
	this->m_pos = rhs.m_pos;
}

Figure& Figure::operator= (const Figure& rhs)
{
	this->m_board = rhs.m_board;
	this->m_color = rhs.m_color;
	this->m_pos = rhs.m_pos;
	return *this;
}

void Figure::draw(Graphics::Window& window)
{ 
	window.draw(*this); 
}
