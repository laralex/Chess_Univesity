#pragma once

#include "stdafx.h"

// Таймер с минутами и секундами

class Clock
{
	public:
		Clock(uint min = 0, uint sec = 0) 
		: min(min), sec(sec)
		{ }
		Clock(const Clock&);
		// Установить определенное время
		void setClock(uint min = 10, uint sec = 0);
		// Тик на следующую секунду
		bool tick_one_sec();
		bool operator--();
		// Вывести значение таймера в строку
		std::string formString();
	private:
		uint min, sec;
};