#include "stdafx.h"
#include "parser-ini.h"
#include <fstream>

using namespace std;
using namespace Utils;


// Функтор добавления секции
struct add_section
{
	IniDataMap & data_;
	add_section(IniDataMap & data) : data_(data) {}
	void operator() (const string& section_name)
	{
		// Добавить секцию по имени string(p,q) с пустым словарем записей
		data_.insert(Section(section_name, SectionMap()));
	}
};

// Функтор добавления записи
struct add_entry
{
	IniDataMap & data_;
	const string * section;

	add_entry(IniDataMap & data) : data_(data) {}
	void setSection(const string* section){ this->section = section; }
	void operator()(StrIterator keyp, StrIterator keyq,
		StrIterator valp, StrIterator valq)
	{
		// Все секции->Текущая секция->
		// Добавить запись с ключом и значением
		data_[*section].insert(Entry(string(keyp, keyq), string(valp, valq)));
	}
};

void ParserIni::parse(const std::string& filepath)
{
	// Очищаем данные
	data.clear();
	// Функторы добавления ключей и секций
	add_section addSection(data);
	add_entry addEntry(data);
	// Построчное чтение файла
	std::string line, section;
	std::ifstream input(filepath);
	if (!input.is_open())
		throw exceptions::file_not_open(filepath);
	StrIterator iter;
	while (!input.eof())
	{
		getline(input, line);
		if (line.empty()) continue; // Пустые строки пропускаем
		if (*line.begin() == _T('[') && *(line.end() - 1) == _T(']'))
		{
			// Секция определяется шаблоном [.....]
			section = string(line.begin() + 1, line.end() - 1);
			addEntry.setSection(&section);
			addSection(section);
		}
		else
		{
			// Пара ключ-значение определяется шаблоном .....=.......
			for (iter = line.begin(); iter < line.end(); ++iter)
			{
				if (*iter == _T('='))
				{
					addEntry(line.begin(), iter, iter + 1, line.end());
					break;
				}
			}
			
		} // Неподходящие под эти шаблоны строчки не обрабатываются	
	}
}

SectionMap& ParserIni::operator[](const std::string& section)
{
	return data[section];
}

Section * ParserIni::getSection(const std::string& name)
{
	for (auto it = data.begin(); it != data.end(); ++it)
	{
		if (it->first == name) return &(*it);
	}
	throw exceptions::invalid_key("Invalid section");
}