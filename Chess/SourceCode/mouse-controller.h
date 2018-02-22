#pragma once

#include "mouse-behaviour.h"
#include "window.h"

namespace Utils
{
	// Обработчик - обертка для мыши

	class MouseController
	{
		// Мышка
		sf::Mouse m_mouse;
		// Привязка к окну
		Graphics::Window& m_window;
		// Наблюдатели - те объекты реализующие MouseBehaviour, которые приписаны к обработчику
		std::vector<MouseBehaviour*> m_observers;
		// Событие окна
		sf::Event m_window_event;
	public:

		MouseController(Graphics::Window& window) 
			: m_mouse(), m_window(window), m_observers()
		{ }

		// Добавить наблюдателя
		void addObserver(MouseBehaviour* new_observer);
		// Удалить наблюдателя
		void removeObserver(MouseBehaviour* observer);
		// Обработать события мыши ВСЕХ привязанных наблюдателей
		void processMouseEvents(const sf::Event& window_event);
		// Получить позицию мышки
		sf::Vector2i getPosition() {return m_mouse.getPosition(m_window);}
	};
}