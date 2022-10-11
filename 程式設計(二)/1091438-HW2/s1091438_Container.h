#pragma once
#include<iostream>
using namespace std;

class Container
{
	friend ostream &operator<<(ostream &, Container test);
	friend istream &operator>>(istream &out, Container &test);
public:
	Container(int); //�إߪŮe���]��J�Ȭ��e���j�p�^
	void push(int);
	int pop(); //�����̫��J���æ^�ǲ��X���]�S���h��0�^
	void printALL(); //�L�X�Ҧ����e�A�t���~�T��+����C
	void resize(int); //���ܮe���j�p
	static Container cat(Container&, Container&);//�X��Container�A�^�ǦX�֦n��
	Container operator+(const Container&);//C = A+B �\��Pcat,��A�PB����
	Container operator+(int);//C = A + 3�\��Ppush, ��A����
private:
	int *Array;
	int check = 0;
	int size;
};
