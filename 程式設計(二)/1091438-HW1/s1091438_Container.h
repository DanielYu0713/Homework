#pragma once
#include<vector>
#include"s1091438_Date.h"
using namespace std;
class Container
{
public:
	Container(int); //�إߪŮe���]��J�Ȭ��e���j�p�^
	void addDate(Date);
	void removeLast(); //�����̫��J���]�S�o���ɵL�@�Ρ^
	void printALL(); //�L�X�Ҧ����
private:
	vector <Date> dates2;
};