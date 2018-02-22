
#include "stdafx.h"
#include "visual-block.h"

using namespace Graphics;

VisualBlock::VisualBlock(float x, float y, float width, float height)
	: RectangleShape(sf::Vector2f(width,height))
{
		RectangleShape::setPosition(sf::Vector2f(x, y));
}

VisualBlock::VisualBlock()
	: VisualBlock(0,0,200,200)
{ }

void VisualBlock::setPosition(const sf::Vector2f& new_pos) 
{ RectangleShape::setPosition(new_pos); }

void VisualBlock::setPosition(float x, float y) 
{ RectangleShape::setPosition(sf::Vector2f(x, y));}

void VisualBlock::setSize(const sf::Vector2f& new_size) 
{ RectangleShape::setSize(new_size); }

void VisualBlock::setSize(float x, float y) 
{ RectangleShape::setSize(sf::Vector2f(x, y)); }

void VisualBlock::setFillColor(const sf::Color& color) 
{ RectangleShape::setFillColor(color);}

void VisualBlock::setTexture(const sf::Texture* texture)
{RectangleShape::setTexture(texture);}

float VisualBlock::getX()  const{ return RectangleShape::getPosition().x; }
float VisualBlock::getY() const { return RectangleShape::getPosition().y; }
float VisualBlock::getWidth() const { return RectangleShape::getSize().x; }
float VisualBlock::getHeight() const { return RectangleShape::getSize().y; }

bool VisualBlock::intersectsWith(float x, float y) const
{
	float mx = RectangleShape::getPosition().x;
	float my = RectangleShape::getPosition().y;
	return x >= mx && y >= my && x <= mx + getWidth() && y <= y + getHeight();
}

bool VisualBlock::intersectsWith(const sf::Vector2f& vec) const
{
	return intersectsWith(vec.x, vec.y);
}

bool VisualBlock::intersectsWith(const sf::Vector2i& vec) const
{
	return intersectsWith((float)vec.x, (float)vec.y);
}
