#pragma once
#include <iostream>
#include <string>
#include <ctime>
using namespace std;

class clsSystemDate
{
public:
	static string GetSystemDateTimeString()
	{
		// system datetime string
		time_t t = time(0);
		tm *now = localtime(&t);

		short Day, Month, Year, Hour, Minute, Second;

		Year = now->tm_year + 1900;
		Month = now->tm_mon + 1;
		Day = now->tm_mday;
		Hour = now->tm_hour;
		Minute = now->tm_min;
		Second = now->tm_sec;

		return (to_string(Day) + "/" + to_string(Month) + "/" + to_string(Year) + " - " + to_string(Hour) + ":" + to_string(Minute) + ":" + to_string(Second));
	}
};
