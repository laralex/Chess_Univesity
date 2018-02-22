#pragma once

#include "visual-block.h"
#include "ui-element.h"

namespace Graphics
{
	class PopupMessage : public VisualBlock
	{
	protected:
		std::vector<UIElement*> m_content;
	public:
		virtual void draw(Window& window) = 0;
		virtual ~PopupMessage();
	};

	class TextMessage : public PopupMessage 
	{
	public:
		TextMessage(const std::string& text);
		void draw(Window& window);
	};
}
