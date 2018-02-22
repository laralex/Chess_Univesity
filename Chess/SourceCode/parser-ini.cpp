#include "stdafx.h"
#include "parser-ini.h"
#include <fstream>

using namespace std;
using namespace Utils;


// ������� ���������� ������
struct add_section
{
	IniDataMap & data_;
	add_section(IniDataMap & data) : data_(data) {}
	void operator() (const string& section_name)
	{
		// �������� ������ �� ����� string(p,q) � ������ �������� �������
		data_.insert(Section(section_name, SectionMap()));
	}
};

// ������� ���������� ������
struct add_entry
{
	IniDataMap & data_;
	const string * section;

	add_entry(IniDataMap & data) : data_(data) {}
	void setSection(const string* section){ this->section = section; }
	void operator()(StrIterator keyp, StrIterator keyq,
		StrIterator valp, StrIterator valq)
	{
		// ��� ������->������� ������->
		// �������� ������ � ������ � ���������
		data_[*section].insert(Entry(string(keyp, keyq), string(valp, valq)));
	}
};

void ParserIni::parse(const std::string& filepath)
{
	// ������� ������
	data.clear();
	// �������� ���������� ������ � ������
	add_section addSection(data);
	add_entry addEntry(data);
	// ���������� ������ �����
	std::string line, section;
	std::ifstream input(filepath);
	if (!input.is_open())
		throw exceptions::file_not_open(filepath);
	StrIterator iter;
	while (!input.eof())
	{
		getline(input, line);
		if (line.empty()) continue; // ������ ������ ����������
		if (*line.begin() == _T('[') && *(line.end() - 1) == _T(']'))
		{
			// ������ ������������ �������� [.....]
			section = string(line.begin() + 1, line.end() - 1);
			addEntry.setSection(&section);
			addSection(section);
		}
		else
		{
			// ���� ����-�������� ������������ �������� .....=.......
			for (iter = line.begin(); iter < line.end(); ++iter)
			{
				if (*iter == _T('='))
				{
					addEntry(line.begin(), iter, iter + 1, line.end());
					break;
				}
			}
			
		} // ������������ ��� ��� ������� ������� �� ��������������	
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