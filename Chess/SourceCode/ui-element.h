#pragma once

#include "visual-block.h"
#include "textable.h"

namespace Graphics
{
	class UIElement : public VisualBlock
	{
	public:
		virtual void draw(Graphics::Window& window) = 0;
		virtual void build() = 0;
	};

	class Label : public UIElement, public Textable
	{
		sf::Text m_text;
	public:
		Label(const std::string& text);
		void draw(Graphics::Window& window);
		void build();
	};
}
