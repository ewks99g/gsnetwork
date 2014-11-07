#pragma once
#include <stdio.h>
#include <string.h>


struct TTestStaticStructNew
{
	int nVal1;
	int nVal2;
	int nVal3;
	int nVal4;
};


void test_static_struct_new();


class TestNullObject
{
	public:
		inline void printAll() {printf("%d,%d\n",30,30);}
	private:
		int a_;
		int b_;
};

struct SBitTimeDate{
unsigned short  year    : 9; 
unsigned short  month   : 4; 
unsigned short  wday    : 3; 
unsigned int  day     : 12;
unsigned int  hour    : 5; 
unsigned int  minute  : 6; 
unsigned char   second  : 6; 
};

struct STimeDate
{
	unsigned int	year	: 12;		// 2000 ~
	unsigned int	month	: 10;		//[1-12]
	unsigned int	wday	: 10;		//[1-7]
	unsigned int	day		: 13;		//[1-31]
	unsigned int	hour	: 5;		//[0-23]
	unsigned int	minute	: 6;		//[0-59]
	unsigned int	second  : 8;			//[0-59]

//计算从fromTime间隔subDay天数之前的时间，存放在toTime中
	int getHistoryDayTime(const STimeDate& fromTime, STimeDate& toTime, int subDay)
	{
		toTime = fromTime;
	
		for (int _i = 0; _i < subDay; _i++)
		{
			int _year,_month,_day;
			toTime.yesterday(_year,_month,_day);
			toTime.year = _year;
			toTime.month = _month;
			toTime.day = _day;
		}
	}
	//计算昨天的时间
	void yesterday(int& rstYear,int& rstMonth,int& rstDay)
	{
		//一个月内
		if (day > 1)
		{
			rstMonth = month;
			rstDay = day - 1;
			rstYear = year;
			return;
		}
		
		//算出月数
		if (month == 1)
		{
			rstMonth = 12;
			rstYear = year - 1;
		}
		else
		{
			rstMonth = month - 1;
			rstYear = year;
		}
		if(month == 1 || month == 2 || month == 4 || month == 6 || month == 8 || month == 9 || month == 11)
		{
			rstDay = 31;
		}
		else if (month == 5 || month == 7 || month == 10 || month == 12)
		{
			rstDay = 30;
		}
		else if (month == 3)
		{
			if((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
			{
				rstDay = 29;
			}
			else
			{
				rstDay = 28;
			}
		}
			
	}
	//计算从fromTime间隔subDay天数之后的时间，存放在toTime中
	int getFutureDayTime(const STimeDate& fromTime, STimeDate& toTime, int subDay)
	{
		toTime = fromTime;
		for (int _i = 0; _i < subDay; _i++)
		{
			int _year,_month,_day;
			toTime.tomorrow(_year,_month,_day);
			toTime.year = _year;
			toTime.month = _month;
			toTime.day = _day;
		}
	}
	//计算明天的时间
	void tomorrow(int& rstYear,int& rstMonth,int& rstDay)
	{
		//一个月内
		if (day == 31)
		{
			rstYear = year;
			rstMonth = month + 1;
			rstDay = 1;
		}
		else if (day == 30)
		{
				if(month == 4 || month == 6 || month == 9)
				{
					rstYear = year;
					rstMonth = month + 1;
					rstDay = 1;
				}
				else if (month == 12)
				{
					rstYear = year + 1;
					rstMonth = 1;
					rstDay = 1;
				}
				else
				{
					rstYear = year;
					rstMonth = month;
					rstDay = day + 1;
				}
		}else if (day == 29)
		{
				if (month == 2)
				{
					rstYear = year;
					rstMonth = month + 1;
					rstDay = 1;
				}
				else
				{
					rstYear = year;
					rstMonth = month;
					rstDay = day + 1;
				}
		}
		else if (day == 28)
		{
			if (month == 2)
			{
				/*year with 29 days*/
				if((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
				{
					rstYear = year;
					rstMonth = month;
					rstDay = day + 1;
				}
				else
				{
					rstYear = year;
					rstMonth = month + 1;
					rstDay = 1;
				}
			}
			else
			{
				rstYear = year;
				rstMonth = month;
				rstDay = day + 1;
			}
		}
		else
		{
			rstYear = year;
			rstMonth = month;
			rstDay = day + 1;
		}
	}
};

typedef struct SDelayInfo { SDelayInfo(){};
								SDelayInfo(const SDelayInfo& ot) { memcpy(this,&ot,sizeof(SDelayInfo)); }
								SDelayInfo(unsigned short _s,unsigned char _l) : sid(_s),level(_l) {}
								unsigned short sid;unsigned char level; } TDelayInfo;
