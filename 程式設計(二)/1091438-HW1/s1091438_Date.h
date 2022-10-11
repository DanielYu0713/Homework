#pragma once
class Date
{
public:
	Date();
	void setDate(int, int, int);
	int getYear();
	int getMonth();
	int getDay();
	bool earlier(const Date&); //計算誰比較早
	int distance(const Date&); //計算兩個日期差幾天
	void print(); //範例: 2020/3/5
private:
	int year;
	int month;
	int day;
};