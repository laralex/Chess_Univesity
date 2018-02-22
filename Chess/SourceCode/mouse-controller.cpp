
#include "stdafx.h"
#include "mouse-controller.h"

using namespace Utils;
void MouseController::processMouseEvents(const sf::Event& window_event)
{
	bool is_released = (window_event.type == sf::Event::MouseButtonReleased);
	//is_pressed = (window_event.type == sf::Event::MouseButtonPressed),
	sf::Vector2i mouse_pos = getPosition();
	// Оповещаем наблюдателей
	for (auto observer : m_observers)
	{
		// Если ему требуется обработать мышку
		if (observer->needsToProcessMouse(mouse_pos))
		{
			// Он ее обработает
			observer->setActive(true);
			observer->hover(mouse_pos);
			if(m_mouse.isButtonPressed(sf::Mouse::Left))
				observer->mouse_down(mouse_pos);
			if (is_released) 
				observer->mouse_up(mouse_pos);
		}
		else if (observer->isActive())
		{
			// Иначе, если мы покидаем объект, от вызываем событие dishover
			observer->setActive(false);
			observer->dishover(mouse_pos);
		}
	}
}

void MouseController::addObserver(MouseBehaviour* new_observer)
{
	for (auto it = m_observers.begin(); it != m_observers.end(); ++it)
	{
		if (*it == new_observer) return;
	}
	m_observers.push_back(new_observer);
}

void MouseController::removeObserver(MouseBehaviour* observer)
{
	for (auto it = m_observers.begin(); it != m_observers.end(); ++it)
	{
		if (*it == observer)
		{
			m_observers.erase(it);
			break;
		}
	}
}