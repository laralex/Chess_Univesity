#pragma once

#include "window.h"

namespace Graphics
{
	// ������������� �������������� ���� 
	class VisualBlock : protected sf::RectangleShape
	{
	protected:
		
	public:
		VisualBlock(float x, float y, float width, float height);
		VisualBlock();
		// ���������
		virtual void setPosition(const sf::Vector2f& new_pos);
		virtual void setPosition(float x, float y);
		virtual void setSize(const sf::Vector2f& new_size);
		virtual void setSize(float x, float y);
		virtual void setFillColor(const sf::Color& color = sf::Color(0,0,0,0));
		virtual void setTexture(const sf::Texture* texture);
		
		// ��� ���������� ������ ����� ���� ������������ ���, ��� �� ���������
		virtual void draw(Graphics::Window& window) = 0;

		// ������ � ���������� 
		float getX() const;
		float getY() const;
		float getWidth() const;
		float getHeight() const;
		
		// ����������, ����������� �� ������ ����� ����� 
		bool intersectsWith(const sf::Vector2i& vec) const;
		bool intersectsWith(const sf::Vector2f& vec) const;
		bool intersectsWith(float x, float y) const;
	};
}

