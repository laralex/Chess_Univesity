#pragma once

#include "mouse-behaviour.h"
#include "window.h"

namespace Utils
{
	// ���������� - ������� ��� ����

	class MouseController
	{
		// �����
		sf::Mouse m_mouse;
		// �������� � ����
		Graphics::Window& m_window;
		// ����������� - �� ������� ����������� MouseBehaviour, ������� ��������� � �����������
		std::vector<MouseBehaviour*> m_observers;
		// ������� ����
		sf::Event m_window_event;
	public:

		MouseController(Graphics::Window& window) 
			: m_mouse(), m_window(window), m_observers()
		{ }

		// �������� �����������
		void addObserver(MouseBehaviour* new_observer);
		// ������� �����������
		void removeObserver(MouseBehaviour* observer);
		// ���������� ������� ���� ���� ����������� ������������
		void processMouseEvents(const sf::Event& window_event);
		// �������� ������� �����
		sf::Vector2i getPosition() {return m_mouse.getPosition(m_window);}
	};
}