#pragma once

#include "stdafx.h"

typedef std::pair<const std::string, std::string> Entry; // 1 ������ ����-��������
typedef std::map <const std::string, std::string> SectionMap;
typedef std::pair<const std::string, SectionMap> Section;
typedef std::map <const std::string, SectionMap> IniDataMap;
typedef std::string::iterator StrIterator; // ��������� ��������
typedef std::string::const_iterator ConstStrIterator;

namespace Utils
{
	// ������ ini ������ � ������� �������� (������ - ���� - ��������)
	class ParserIni
	{
		// ������ � ����
		IniDataMap data;
		
		// ����� - ��������, ������ ��������
		ParserIni() {}
		~ParserIni() {}
		ParserIni(const ParserIni&) = delete;
		ParserIni& operator= (const ParserIni&) = delete;
	public:
		static ParserIni& getInstance()
		{
			// �������� �������
			static ParserIni singleton;
			return singleton;
		}

		// ��������� ������� ����� �����
		void parse(const std::string& filepath);

		// ������ � ������� ����-�������� �� ������
		SectionMap& operator[](const std::string&);

		// ������ � ������
		Section * getSection(const std::string& name);
	};
}


