#pragma once

#include "stdafx.h"

typedef std::pair<const std::string, std::string> Entry; // 1 запись ключ-значение
typedef std::map <const std::string, std::string> SectionMap;
typedef std::pair<const std::string, SectionMap> Section;
typedef std::map <const std::string, SectionMap> IniDataMap;
typedef std::string::iterator StrIterator; // Строковый итератор
typedef std::string::const_iterator ConstStrIterator;

namespace Utils
{
	// Парсер ini файлов в словарь словарей (секция - ключ - значение)
	class ParserIni
	{
		// Данные в куче
		IniDataMap data;
		
		// Класс - синглтон, запрет создания
		ParserIni() {}
		~ParserIni() {}
		ParserIni(const ParserIni&) = delete;
		ParserIni& operator= (const ParserIni&) = delete;
	public:
		static ParserIni& getInstance()
		{
			// Синглтон парсера
			static ParserIni singleton;
			return singleton;
		}

		// Запустить парсинг этого файла
		void parse(const std::string& filepath);

		// Доступ к словарю ключ-значение по секции
		SectionMap& operator[](const std::string&);

		// Доступ к секции
		Section * getSection(const std::string& name);
	};
}


