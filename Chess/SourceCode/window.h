#pragma once

#include "stdafx.h"

namespace Graphics
{
	// Обертка для создания SFML окна
	class Window : public sf::RenderWindow
	{
	private:
	public:
		Window(uint w = 500, uint h = 500, const std::string& title = "Window");
		void create(uint w = 500, uint h = 500, const std::string& title = "Window");
	};

}