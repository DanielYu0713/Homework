#include<iostream>
#include "s1091438_Date.h"
#include "s1091438_Container.h"
using namespace std;

Container::Container(int n) {};//建立空容器（輸入值為容器大小）
void Container::addDate(Date dates) {
	dates2.push_back(dates);
};
void Container::removeLast() {
	dates2.pop_back();
}; //移除最後放入的（沒得移時無作用）
void Container::printALL() {
	for (int i = 0; i < dates2.size(); i++) {
		if (i == 0) {
			dates2[i].print();
		}
		else {
			dates2[i].print();
			if (dates2[i].distance(dates2[i - 1]) < 0) {
				cout << " (" << dates2[i].distance(dates2[i - 1]) << ")";
			}
			else {
				cout << " (+"<<dates2[i].distance(dates2[i - 1])<< ")";
			}
		}
		cout << endl;
	}
};//印出所有日期
