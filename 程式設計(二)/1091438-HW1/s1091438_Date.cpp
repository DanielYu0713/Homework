#include<iostream>
#include<stdlib.h>
#include<time.h>
#include "s1091438_Date.h"
using namespace std;

int judge(int y, int m) {
	if (m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12) {
		return 31;
	}
	if (m == 4 || m == 6 || m == 9 || m == 11) {
		return 30;
	}
	if (m == 2) {
		if (y % 4 == 0 && y % 100 != 0 && y != 0 || y % 400 == 0 && y != 0) {
			return 29;
		}
		else {
			return 28;
		}
	}
}

Date::Date() {
	int rand_y, rand_m, rand_d;
	rand_y = rand() % 23 + 1999;
	rand_m = rand() % 12 + 1;
	rand_d = rand() % judge(rand_y, rand_m) + 1;
	setDate(rand_y, rand_m, rand_d);
}
void Date :: setDate(int y, int m, int d) {
	year = y;
	month = m;
	day = d;
}
int Date::getYear() {
	return year;
}
int Date::getMonth() {
	return month;
}
int Date::getDay() {
	return day;
}
bool Date::earlier(const Date& early) {
	if (year > early.year) {
		return true;
	}
	if (year < early.year) {
		return false;
	}
	if (month > early.month) {
		return true;
	}
	if (month < early.month) {
		return false;
	}
	if (day > early.day) {
		return true;
	}
	if (day < early.day) {
		return false;
	}
}
int Date::distance(const Date& dir) {
		int total_1 = 0;
		int total_2 = 0;
		
		total_1 = (year - 1999) * 365 + (year - 1999) / 4 - (year - 1999) / 100 + (year - 1999) / 400;
		for (int i = 1; i < month; i++) {
			total_1 += judge(year, i);
		}	
		total_1 += day;//前面總和
		
		total_2 = (dir.year - 1999) * 365 + (dir.year - 1999) / 4 - (dir.year - 1999) / 100 + (dir.year - 1999) / 400;
		for (int j = 1; j < dir.month; j++) {
			total_2 += judge(dir.year, j);
		}
	
		total_2 += dir.day;//後面總和
		return total_1 - total_2;
	};//計算兩個日期差幾天
void Date::print() {
	cout << getYear() << "/" << getMonth() << "/" << getDay();
};