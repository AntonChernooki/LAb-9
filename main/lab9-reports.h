#ifndef LAB_REPORT
#define LAB_REPORT
#include "constans.h"
struct times
{
	int hour;
	int minutes;
};
struct person
{
	char first_name[MAX_STRING_SIZE];
	char middle_name[MAX_STRING_SIZE];
	char last_name[MAX_STRING_SIZE];
};
struct dok
{
	times start;
	times finish;
	person author;
	char theme[MAX_STRING_SIZE];
	int length;
};
#endif