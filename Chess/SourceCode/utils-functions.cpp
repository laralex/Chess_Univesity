#include "stdafx.h"
#include "utils-functions.h"

using namespace std;

bool Utils::recognize_bool(const string& str)
{
	if (str == "1" || str == "true") return true;
	if (str == "0" || str == "false") return false;
	throw bad_cast();
}

int Utils::recognize_int(const string& str)
{
	return stoi(str);
}

float Utils::recognize_float(const std::string& str)
{
	return stof(str);
}

int iter_recognize_int(ConstStrIterator& p, ConstStrIterator& q)
{
	return Utils::recognize_int(string(p, q));
}

sf::Color Utils::recognize_color(const string& str)
{
	bool has_one_component = false;
	uint r, g;
	auto num_begin = str.begin();
	for (auto it = str.begin(); it != str.end(); ++it)
	{
		if (*it == _T(':'))
		{
			if (has_one_component)
			{
				g = iter_recognize_int(num_begin, it);
				num_begin = it + 1;
				break;
			}
			else
			{
				r = iter_recognize_int(num_begin, it);
				num_begin = it + 1;
				has_one_component = true;
			}

		}
	}
	return sf::Color(r, g, iter_recognize_int(num_begin, str.end()));
}