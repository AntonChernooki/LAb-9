#include "processing.h"
dok* process(dok* report[], int size)
{
	dok* proc = new dok;
	int max = 0;
	for (int i = 0; i < size; i++)
	{
		if (report[i]->length > report[max]->length)
			max = i;
	}
	int hours = 0, minute;
	minute = report[max]->length;
	while (minute > 60)
	{
		hours++;
		minute = minute - 60;
	}
	proc->start.hour = hours;
	proc->start.minutes = minute;
	return proc;
}

