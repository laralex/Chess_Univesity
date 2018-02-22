#pragma once

#include "stdafx.h"
#include "window.h"

namespace Graphics
{
	// Блок с элементами (преимущественно визуальными)  
	class Block
	{
	protected:
		sf::Vector2f pos, size;
	public:
		Block(const sf::Vector2f& pos = sf::Vector2f(0, 0),
					const sf::Vector2f& size = sf::Vector2f(100, 100))
			: pos(pos), size(size) 
		{ }
		Block(float x, float y, float width, float height)
			: Block(sf::Vector2f(x, y), 
						  sf::Vector2f(width, height))
		{ }

		virtual void draw(Graphics::Window& window) = 0;

		void setPosition(const sf::Vector2f& new_pos) { pos = new_pos; }
		void setPosition(float x, float y) { setPosition(sf::Vector2f(x, y)); }
		void setSize(const sf::Vector2f& new_size) {  size = new_size; }
		void setSize(float x, float y) { setSize(sf::Vector2f(x, y)); }


		void scale(float offsetX, float offsetY) { size.x *= offsetX; size.y *= offsetY;}
		void move(float offsetX, float offsetY) { pos.x += offsetX; pos.y += offsetY;}
		void scale(const sf::Vector2f& offset) { scale(offset.x, offset.y); }
		void move(const sf::Vector2f& offset) { move(offset.x,offset.y); }

		
	};
}

