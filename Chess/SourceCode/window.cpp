#include "stdafx.h"
#include "window.h"

using namespace Graphics;
using namespace std;

Window::Window(uint width, uint height, const string& title)
{
	create(width, height, title);
}

void Window::create(uint width, uint height, const string& title)
{
	RenderWindow::create(sf::VideoMode(width, height), title, sf::Style::Close);
	RenderWindow::setVerticalSyncEnabled(true);
	RenderWindow::setFramerateLimit(60);
}
