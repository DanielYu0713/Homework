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
};//�Ĥ@�ӰѼƬOostream���A���ѼơA�]�N�O��X��y�A�Ǧ^�o�Ӧ�y��cout���ܡA�N�i�H��ܿ�X�ܦ�y������T�A�ĤG�ӰѼƬO�n��X������A��@�ɱN���w��X����T
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
};//�ĤG�ӰѼƥ����O�ѦҡA�o�ˤ~�i�H�N��T���w���ҭn������A�Ӥ��O�@�ӽƻs����
Container::Container(int x){
	Array = new int[x];
	size = x;
	for (int i = 0; i < size; i++){
		Array[i] = 0;
	}// initial
};//�إߪŮe���]��J�Ȭ��e���j�p�^
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
};//�����̫��J���æ^�ǲ��X���]�S���h��0�^
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
};//�L�X�Ҧ����e�A�t���~�T��+����C
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
};//���ܮe���j�p
Container Container::cat(Container &A, Container &B){
	return A + B;
};//�X��Container�A�^�ǦX�֦n��
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
};//C = A+B �\��Pcat,��A�PB����
Container Container::operator+(int plus) {
	push(plus);
	return *this;
};//C = A + 3�\��Ppush, ��A����
