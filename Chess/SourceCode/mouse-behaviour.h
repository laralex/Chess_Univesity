#pragma once

#include "stdafx.h"

// ��������� �������, ������� ����� ������������ ������� ����

class MouseBehaviour
{
protected:
	bool is_active;
	MouseBehaviour() {}
public:
	// �������� ��� ��������� �����
	virtual void hover(const sf::Vector2i& vec) = 0; 
	// �������� ��� ��������� ������� �����
	virtual void dishover(const sf::Vector2i& vec) = 0;	
	// �������� ��� ������� ������� ����
	virtual void mouse_down(const sf::Vector2i& vec) = 0;
	// �������� ��� ���������� ������� ����
	virtual void mouse_up(const sf::Vector2i& vec) = 0;

    // ������ ������, ����� �� ��� ������������ ���� ��� ���
	virtual bool needsToProcessMouse(const sf::Vector2i& vec) = 0; 
	
	// ���������� ������� �� ��������������
	void setActive(bool is_active) { this->is_active = is_active; }	
	bool isActive() const { return is_active; }
};