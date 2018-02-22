#pragma once

#include "stdafx.h"

namespace exceptions
{
	class file_not_open : public std::logic_error
	{
		std::string what;
	public:
		file_not_open(const std::string& file) : what(file), std::logic_error("File is not open") {}
	};

	class invalid_key : public std::logic_error
	{
		std::string what;
	public:
		invalid_key(const std::string& key) : what(key), std::logic_error("This key is invalid to access") {}
	};
}
