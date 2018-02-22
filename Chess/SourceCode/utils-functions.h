#pragma once

#include "stdafx.h"

// Вспомогательные функции (распознавание в строке значений)

namespace Utils
{
	bool recognize_bool(const std::string& str);
	int recognize_int(const std::string& str);
	float recognize_float(const std::string& str);
	sf::Color recognize_color(const std::string& str);
}

