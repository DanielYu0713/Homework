#include<iostream>
#include<windows.h>
#include<string>
#include<fstream>
#include<stdexcept>
#include"s1091438BigNUMv4.h"
using namespace std;


BigNUM::BigNUM(string file) {
	ifstream infile(file, ifstream::in);
	if (!infile.good()) {
		infile.close();
		cout << file << "open fail!!";
		return;
	}
	for (string s; !infile.eof();) {
		infile >> s;
		for (int i = 0; i < s.size(); i++)
		{
			this->push_back(s[i] - '0');
		}
	}
	infile.close();
}
BigNUM BigNUM::operator+(const string&str) {
	for (int i = 0; i < str.size(); i++) {
		this->push_back(str[i] - '0');
	}
	return *this;
}

BigNUM BigNUM::operator+(const BigNUM& str)const {
	BigNUM tmp;
	int a = max(this->getSize(), str.getSize()) + 1;
	int *A = new int[a];
	int *B = new int[a];
	int *sum = new int[a];

	for (int i = 0; i < a; i++) {
		A[i] = 0;
		B[i] = 0;
		sum[i] = 0;
	}

	for (int i = this->getSize() - 1, j = 0; i >= 0; i--, j++)
	{
		A[j] = (*this)[i];

	}

	for (int i = str.getSize() - 1, j = 0; i >= 0; i--, j++)
	{
		B[j] = str[i];

	}

	//癴

	int carry = 0;
	for (int i = 0; i < a; i++)
	{
		sum[i] = A[i] + B[i] + carry;
		if (sum[i] >= 10) {
			sum[i] -= 10;
			carry = 1;
		}
		else {
			carry = 0;
		}
	}//㎝秈

	int start = 0;
	for (int i = a - 1; i >= 1; i--) {
		if (sum[i] != 0) {
			start = i;
			break;
		}
	}//т材竚
	for (int i = start; i >= 0; i--) {
		tmp.push_back(sum[i]);
	}


	delete[]A;
	delete[]B;
	delete[]sum;
	return tmp;
}

BigNUM BigNUM::operator-(const BigNUM& str)const {
	BigNUM tmp;
	int a = max(getSize(), str.getSize());//搭程计
	int *A = new int[a];
	int *B = new int[a];
	int *subtract = new int[a];
	for (int i = 0; i < a; i++) {
		A[i] = 0;
		B[i] = 0;
		subtract[i] = 0;
	}

	for (int i = this->getSize() - 1, j = 0; i >= 0; i--, j++)
	{
		A[j] = (*this)[i];

	}

	for (int i = str.getSize() - 1, j = 0; i >= 0; i--, j++)
	{
		B[j] = str[i];

	}
	//
	int bit = 0;
	for (int i = 0; i < a; i++)
	{
		A[i] -= bit;
		if (A[i] < B[i])
		{
			A[i] += 10;
			bit = 1;
		}
		else {
			bit = 0;
		}
		subtract[i] = A[i] - B[i];
	}
	int start = 0;
	for (int i = a - 1; i >= 0; i--) {
		if (subtract[i] != 0) {
			start = i;
			break;
		}
	}//т材竚
	for (int i = start; i >= 0; i--) {
		tmp.push_back(subtract[i]);
	}
	delete[]A;
	delete[]B;
	delete[]subtract;
	return tmp;
}
BigNUM BigNUM::operator*(const BigNUM& str) const {
	BigNUM tmp;
	int a = getSize() + str.getSize();
	int *A = new int[a];
	int *B = new int[a];
	int *product = new int[a*a];
	for (int i = 0; i < a; i++) {
		A[i] = 0;
		B[i] = 0;

	}
	for (int i = 0; i < a*a; i++) {
		product[i] = 0;
	}

	for (int i = this->getSize() - 1, j = 0; i >= 0; i--, j++)
	{
		A[j] = (*this)[i];

	}

	for (int i = str.getSize() - 1, j = 0; i >= 0; i--, j++)
	{
		B[j] = str[i];

	}
	//癴
	for (int i = 0; i < a; i++) {
		for (int j = 0; j < a; j++) {
			product[i + j] += A[i] * B[j];
			if (product[i + j] >= 10) {
				product[i + j + 1] += product[i + j] / 10;
				product[i + j] = product[i + j] % 10;
			}
		}
	}
	int start = 0;
	for (int i = a; i >= 0; i--) {
		if (product[i] != 0) {
			start = i;
			break;
		}
	}//玡Τ干箂,硂柑т计竚,盢ウstart

	for (int i = start; i >= 0; i--) {
		tmp.push_back(product[i]);
	}

	delete[]A;
	delete[]B;
	delete[]product;

	return tmp;
}


BigNUM& BigNUM::operator=(const BigNUM& str) {
	this->resize(0);
	for (int i = 0; i < str.getSize(); i++) {
		push_back(str[i]);
	}
	return *this;
}
bool BigNUM::operator>(const BigNUM& r) {
	if (this->getSize() < r.getSize())
		return false;
	else if (this->getSize() > r.getSize())
		return true;

	for (int i = 0; i < r.getSize(); i++) {
		if (operator[](i) < r.operator[](i))
			return false;
		else if (operator[](i) > r.operator[](i))
			return true;
	}
	return false;
}
bool BigNUM::operator<=(const BigNUM& r) {
	return (!(*this > r));
}
bool BigNUM::operator>=(const BigNUM& r) {
	return ((*this > r) || (*this == r));
}
void BigNUM::Swap(BigNUM& A, BigNUM& B) {
	BigNUM tmp = A;
	A = B;
	B = tmp;
}

BigNUM BigNUM::operator/(const BigNUM& right)const {
	BigNUM dividend, divisor, ten, nine, tmp1, quotient;
	nine.push_back(9);
	ten.push_back(1);
	ten.push_back(0);
	for (int i = 0; i < getSize(); i++) {
		dividend.push_back(operator[](i));//砆埃计
	}
	for (int i = 0; i < right.getSize(); i++) {
		divisor.push_back(right.operator[](i));//埃计
	}

	while (!((divisor * ten) > dividend)) {
		divisor.push_back(0);//т程divisor计
	}
	while (divisor > right || divisor == right) {

		for (int i = 1; i < 10; i++) {//tmp1 1~9
			tmp1.resize(0);
			tmp1.push_back(i);
			if ((divisor*tmp1) > dividend) {
				tmp1.pop_back();
				tmp1.push_back(i - 1);
				dividend = dividend - (divisor * tmp1);
				quotient.push_back(i - 1);
				break;
			}
			else if (!((divisor*tmp1) > dividend) && tmp1 == nine) {
				dividend = dividend - (divisor * nine);
				quotient.push_back(9);
				break;
			}
		}
		divisor.pop_back();
	}
	return quotient;
}
BigNUM BigNUM::operator%(const BigNUM&right)const {
	BigNUM dividend, divisor, ten, nine, tmp1, remainder;
	nine.push_back(9);
	ten.push_back(1);
	ten.push_back(0);
	for (int i = 0; i < getSize(); i++) {
		dividend.push_back(operator[](i));//砆埃计
	}
	for (int i = 0; i < right.getSize(); i++) {
		divisor.push_back(right.operator[](i));//埃计
	}

	while (!((divisor * ten) > dividend)) {
		divisor.push_back(0);//т程divisor计
	}
	while (divisor > right || divisor == right) {

		for (int i = 1; i < 10; i++) {//tmp1 1~9
			tmp1.resize(0);
			tmp1.push_back(i);
			if ((divisor*tmp1) > dividend) {
				tmp1.pop_back();
				tmp1.push_back(i - 1);
				dividend = dividend - (divisor * tmp1);
				break;
			}
			else if (!((divisor*tmp1) > dividend) && tmp1 == nine) {
				dividend = dividend - (divisor * nine);
				break;
			}
		}
		divisor.pop_back();
	}
	for (int i = 0; i < dividend.getSize(); i++) {
		remainder.push_back(dividend[i]);
	}
	return remainder;
	/*return dividend - divisor * (dividend / divisor);*/
}
BigNUM BigNUM::GCD(const BigNUM&A, const BigNUM&B) {
	BigNUM n1, n2, zero;
	zero.push_back(0);
	for (int i = 0; i < A.getSize(); i++) {
		n1.push_back(A.operator[](i));//砆埃计
	}
	for (int i = 0; i < B.getSize(); i++) {
		n2.push_back(B.operator[](i));//埃计
	}
	while (!(n1 == zero) && !(n2 == zero))
	{
		if (n2 <= n1)
		{
			n1 = n1 % n2;
		}
		else if (n2 > n1)
		{
			n2 = n2 % n1;
		}
	}

	if (n2 <= n1)
	{
		return n1;
	}
	else
	{
		return n2;
	}
}
BigNUM BigNUM::LCM(const BigNUM&A, const BigNUM&B) {
	BigNUM tmp = A * B / GCD(A, B);
	return tmp;
}
