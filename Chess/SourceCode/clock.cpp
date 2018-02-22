#include "stdafx.h"
#include "clock.h"
#include <iomanip>
using namespace std;

Clock::Clock(const Clock& rhs)
{
	min = rhs.min;
	sec = rhs.sec;
}

bool Clock::tick_one_sec()
{
	if(sec) --sec;
	else if (min)
	{
		--min; sec = 59;
	}
	else return false;
	return true;
}
bool Clock::operator--()
{
	return tick_one_sec();
}
void Clock::setClock(uint min, uint sec)
{
	this->min = min + sec / 60;
	this->sec = sec % 60;
}
string Clock::formString()
{
	stringstream str;	
	str << setw(2) << setfill('0') << min << " : " ;
	str << setw(2) << setfill('0') << sec;
	return str.str();
}