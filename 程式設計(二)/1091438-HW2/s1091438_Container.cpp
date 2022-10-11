#include <iostream>
#include "s1091438_Container.h"
using namespace std;

ostream &operator<<(ostream &out, Container test) {
	for (int i = 0; i < test.size; i++){
		if (i == 0) {
			out << test.Array[i];
		}
		else {
			out << " " << test.Array[i];
		}
	}
	out << endl;
	return out;
};//第一個參數是ostream型態的參數，也就是輸出串流，傳回這個串流給cout的話，就可以顯示輸出至串流中的資訊，第二個參數是要輸出的物件，實作時將指定輸出的資訊
istream &operator>>(istream &in, Container &test) {
	int x;
	for (int i = 0; i < test.size; i++){
		in >> x;
		if (x == -1) {
			break;
		}
		else{
			test.Array[i] = x;
		}
	}
	return in;
};//第二個參數必須是參考，這樣才可以將資訊指定給所要的物件，而不是一個複製物件
Container::Container(int x){
	Array = new int[x];
	size = x;
	for (int i = 0; i < size; i++){
		Array[i] = 0;
	}// initial
};//建立空容器（輸入值為容器大小）
void Container::push(int num){
	if (Array[size - 1] != 0) {
		check = 4;
	} //no place to push, push fail!
	else{
		for (int i = 0; i < size; i++){
			if (Array[i] == 0){
				Array[i] = num;
				break;
			}
        }
	}
};
int Container::pop(){
	int x = 0;
	if (Array[0] == 0){
		check = 3;
	}//no element can pop, pop fail!
	else{
		for (int i = size - 1; i >= 0; i--){
			if (Array[i] != 0){
				x = Array[i];
				Array[i] = 0;
				break;
			}
		}
	}
	return x;
};//移除最後放入的並回傳移出物（沒有則為0）
void Container::printALL() {
	for (int i = 0; i < size; i++) {
		if (i == 0) {
			cout << Array[i];
		}
		else {
			cout << " " << Array[i];
		}
	}
	if (check == 4) {
		cout << " (Push Fail!)";
	}
	else if (check == 3) {
		cout << " (Pop Fail!)" ;
	}
	cout << endl;
	check = 0; 
};//印出所有內容，含錯誤訊息+換行。
void Container::resize(int re){
	int *tmp = new int[re];
	for (int i = 0; i < re; i++){
		tmp[i] = Array[i];
	}
	delete[] Array;  //copy size -> y
	Array = new int[re];

	for (int i = 0; i < re; i++){
		if (i >= size){
			Array[i] = 0;
		}
		else{
			Array[i] = tmp[i];
		}
	} // check
	delete[] tmp;
	size = re;
};//改變容器大小
Container Container::cat(Container &A, Container &B){
	return A + B;
};//合併Container，回傳合併好的
Container Container::operator+(const Container&plus) {
	const int total = size + plus.size;
	Container t(total);
	for (int i = 0; i < size; i++) {
		t.push(Array[i]);
	}
	for (int i = 0; i < plus.size; i++) {
		t.push(plus.Array[i]);
	}
	return t;
};//C = A+B 功能同cat,但A與B不變
Container Container::operator+(int plus) {
	push(plus);
	return *this;
};//C = A + 3功能同push, 但A不變
