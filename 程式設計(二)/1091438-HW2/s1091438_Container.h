#pragma once
#include<iostream>
using namespace std;

class Container
{
	friend ostream &operator<<(ostream &, Container test);
	friend istream &operator>>(istream &out, Container &test);
public:
	Container(int); //建立空容器（輸入值為容器大小）
	void push(int);
	int pop(); //移除最後放入的並回傳移出物（沒有則為0）
	void printALL(); //印出所有內容，含錯誤訊息+換行。
	void resize(int); //改變容器大小
	static Container cat(Container&, Container&);//合併Container，回傳合併好的
	Container operator+(const Container&);//C = A+B 功能同cat,但A與B不變
	Container operator+(int);//C = A + 3功能同push, 但A不變
private:
	int *Array;
	int check = 0;
	int size;
};
