#pragma once

#include "stdafx.h"

// ������ � �������� � ���������

class Clock
{
	public:
		Clock(uint min = 0, uint sec = 0) 
		: min(min), sec(sec)
		{ }
		Clock(const Clock&);
		// ���������� ������������ �����
		void setClock(uint min = 10, uint sec = 0);
		// ��� �� ��������� �������
		bool tick_one_sec();
		bool operator--();
		// ������� �������� ������� � ������
		std::string formString();
	private:
		uint min, sec;
};