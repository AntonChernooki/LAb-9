#include "pch.h"
#include "CppUnitTest.h"
#include "../main/lab9-reports.h"
#include "../main/processing.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace unittestproject
	
{
	int time_time(dok* report)
	{
		int hours, minute;
		hours = report->finish.hour - report->start.hour;
		minute = report->finish.minutes - report->start.minutes;
		while (hours != 0)
		{
			minute = minute + 60;
			hours--;
		}
		return minute;
	}
	dok* build_report(int start_hour, int start_minutes, int finish_hour, int finish_minutes)
	{
		dok* report = new dok;
		report->start.hour = start_hour;
		report->start.minutes = start_minutes;
		report->finish.hour = finish_hour;
		report->finish.minutes = finish_minutes;
		report->length = time_time(report);
		return report;
	}

	//       
	void delete_report(dok* array[], int size)
	{
		for (int i = 0; i < size; i++)
		{
			delete array[i];
		}
	}

	TEST_CLASS(processUnitTest)
	{
	public:

		TEST_METHOD(TestMethod1)
		{
		
			dok* reports[3];
			reports[0] = build_report(14, 20, 16, 00); // 100
			reports[1] = build_report(10, 05, 12, 30); // 145
			reports[2] = build_report(15, 55, 17, 30); // 95
			Assert::AreEqual(2, process(reports, 3)->start.hour);
			Assert::AreEqual(25, process(reports, 3)->start.minutes);
			delete_report(reports, 3);

		}
		TEST_METHOD(TestMethod2)
		{
			dok* reports[4];
			reports[0] = build_report(11, 40, 12, 02); // 22
			reports[1] = build_report(9, 35, 12, 05); // 150
			reports[2] = build_report(13, 35, 14, 15); // 40
			reports[3] = build_report(9, 25, 12, 05); // 160
			Assert::AreEqual(2, process(reports, 4)->start.hour);
			Assert::AreEqual(40, process(reports, 4)->start.minutes);
			delete_report(reports, 4);

		}
		TEST_METHOD(TestMethod3)
		{
			dok* reports[3];
			reports[0] = build_report(14, 20, 16, 00); // 100
			reports[1] = build_report(14, 05, 14, 30); // 25
			reports[2] = build_report(11, 05, 14, 30); // 205
			Assert::AreEqual(3, process(reports, 3)->start.hour);
			Assert::AreEqual(25, process(reports, 3)->start.minutes);
			delete_report(reports, 3);

		}
		TEST_METHOD(TestMethod4)
		{
			dok* reports[3];
			reports[0] = build_report(16, 30, 18, 20); // 110
			reports[1] = build_report(13, 15, 15, 10); // 115
			reports[2] = build_report(11, 55, 13, 00); // 65
			Assert::AreEqual(1, process(reports, 3)->start.hour);
			Assert::AreEqual(55, process(reports, 3)->start.minutes);
			delete_report(reports, 3);

		}
		TEST_METHOD(TestMethod5)
		{
			dok* reports[3];
			reports[0] = build_report(16, 20, 18, 45); // 145
			reports[1] = build_report(11, 55, 13, 30); // 145
			reports[2] = build_report(14, 55, 17, 30); // 155
			Assert::AreEqual(2, process(reports, 3)->start.hour);
			Assert::AreEqual(35, process(reports, 3)->start.minutes);
			delete_report(reports, 3);

		}
	};
}

