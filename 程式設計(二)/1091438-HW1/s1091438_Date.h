#pragma once
class Date
{
public:
	Date();
	void setDate(int, int, int);
	int getYear();
	int getMonth();
	int getDay();
	bool earlier(const Date&); //�p��֤����
	int distance(const Date&); //�p���Ӥ���t�X��
	void print(); //�d��: 2020/3/5
private:
	int year;
	int month;
	int day;
};