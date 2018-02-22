
#include "stdafx.h"
#include "settings-part.h"

using namespace Utils;

SettingsPart::SettingsPart(size_t max_sections) : m_max_sections(max_sections)
{
	m_sections.reserve(max_sections);
}
void SettingsPart::addSection(Section * section)
{
	if (m_sections.size() == m_max_sections)
		throw std::overflow_error("Too many sections passed");
	m_sections.push_back(section);
}
SectionMap& SettingsPart::operator[] (const std::string section)
{
	for (auto it = m_sections.begin(); it != m_sections.end(); ++it)
	{
		if ((*it)->first == section) return (*it)->second;
	}
	throw exceptions::invalid_key("Invalid section");
}

const std::string& SettingsPart::getValue(const std::string& section, const std::string& key)
{
	for (auto it = m_sections.begin(); it != m_sections.end(); ++it)
	{
		if ((*it)->first == section)
		{
			for (auto itMap = (*it)->second.begin(); itMap != (*it)->second.end(); ++itMap)
			{
				if (itMap->first == key) return itMap->second;
			}
		}
	}
	throw exceptions::invalid_key("Wrong Section or Key in settings query");
}

SettingsPart& SettingsPart::operator += (Section * section)
{
	addSection(section);
	return *this;
}