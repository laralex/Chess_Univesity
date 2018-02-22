#pragma once

#include "stdafx.h"
#include "utils-functions.h"

// Кусок настроек, полученный парсингом ini	файла
// Дает доступ только к некоторым секциям настроек

namespace Utils
{
	class SettingsPart
	{
		size_t m_max_sections;
		std::vector<Section*> m_sections;
	public:
		SettingsPart(size_t max_sections);
		void addSection(Section * section);
		SectionMap& operator[] (const std::string);
		const std::string& getValue(const std::string& section, const std::string& key);
		SettingsPart& operator += (Section * section);
	};
}