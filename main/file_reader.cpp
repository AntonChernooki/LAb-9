#include "lab9-reports.h"
#include "constans.h"
#include <fstream>
#include <iostream>
using namespace std;
int dok_time(dok* element)
{
	int hours, minute;
	hours = element->finish.hour - element->start.hour;
	minute = element->finish.minutes - element->start.minutes;
	while (hours != 0)
	{
		minute = minute + 60;
		hours--;
	}
	return minute;
}
times convert(char* str)
{
	times result;
	char* context = NULL;
	char* str_number = strtok_s(str, ":", &context);
	result.hour = atoi(str_number);
	str_number = strtok_s(NULL, " ", &context);
	result.minutes = atoi(str_number);
	return result;
}
void read(const char* file_name, dok* array[], int& size)
{
	std::ifstream file(file_name);
	if (file.is_open())
	{
		size = 0;
		char tmp_buffer[MAX_STRING_SIZE];
		while (!file.eof())
		{
			dok* item = new dok;
			file >> tmp_buffer;
			item->start = convert(tmp_buffer);
			file >> tmp_buffer;
			item->finish = convert(tmp_buffer);
			file >> item->author.last_name;
			file >> item->author.first_name;
			file >> item->author.middle_name;
			file.read(tmp_buffer, 1); // чтения лишнего символа пробела
			file.getline(item->theme, MAX_STRING_SIZE);
			item->length = dok_time(item);
			array[size++] = item;
		}
		file.close();
	}
	else
	{
		throw "Ошибка открытия файла";
	}
}