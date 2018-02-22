#pragma once

#include "stdafx.h"

// Интерфейс объекта, который может обрабатывать события мыши

class MouseBehaviour
{
protected:
	bool is_active;
	MouseBehaviour() {}
public:
	// Действие при наведении мышью
	virtual void hover(const sf::Vector2i& vec) = 0; 
	// Действие при покидании объекта мышью
	virtual void dishover(const sf::Vector2i& vec) = 0;	
	// Действие при зажатой клавише мыши
	virtual void mouse_down(const sf::Vector2i& vec) = 0;
	// Действие при отпускании клавиши мыши
	virtual void mouse_up(const sf::Vector2i& vec) = 0;

    // Объект решает, нужно ли ему обрабатывать мышь или нет
	virtual bool needsToProcessMouse(const sf::Vector2i& vec) = 0; 
	
	// Неактивные объекты не обрабатываются
	void setActive(bool is_active) { this->is_active = is_active; }	
	bool isActive() const { return is_active; }
};