#include <iostream>
#include "s1091438_MyString.h"

using namespace std;
int main()
{
	///To be or not to be, that is the question;
	const char *str1 = "to be "; //This char string ended with '\0' automatically
	const char *str2 = "the ";
	const char *str3 = "or not to be";
	const char *str_tester = "Ha";
	MyString A(str1);
	MyString X(str2);
	MyString B = X;
	MyString C = "or not to be";
	cout << "A = str1: " << A << endl;
	cout << "B = X = str2: " << B << " = " << X << endl;
	cout << "C = str3: " << C << " = " << str3 << endl;

	MyString D = A + C;
	cout << "D = A + C: " << D << endl;
	D = A + str3;
	cout << "D = A + str3: " << D << endl;
	D = str1 + C;
	cout << "D = str1 + C: " << D << endl;

	cout << "-------------------------------" << endl;

	cout << "D push ',': ";
	D.push_back(',');
	cout << D << endl;
	cout << "D pop_back: ";
	D.pop_back();
	cout << D << endl;

	cout << "-------------------------------" << endl;

	MyString STR = D;
	MyString E = ", that is cool question";
	MyString F = ", that is (the )question";
	MyString G = "the ";

	cout << "STR = D append F: " << STR.append(F) << endl;

	cout << "STR erase 28-33: " << STR.erase(28, 6) << endl;

	cout << "STR insert G: " << STR.insert(28, G) << endl;

	cout << "STR erase 28-31: " << STR.erase(28, 4) << endl;

	cout << "STR insert E (10-14): " << STR.insert(28, E, 10, 5) << endl;

	cout << "STR substr(3,len=15): " << STR.substr(3, 15) << endl;

	cout << "STR: " << STR << endl;

	cout << "-------------------------------" << endl;

	MyString STR2(E, 10, 4);
	cout << "find \"cool\" in the STR: " << STR.find(STR2) << endl;

	STR2 = "cXXL";
	cout << "Let STR2 = cXXL: " << STR2 << endl;

	cout << "find \"cXXL\" in the STR: " << STR.find(STR2) << endl;

	cout << "find first \"cXXL\" in the STR: " << STR.find_first_of(STR2) << endl;

	cout << "print the first and last char of STR: " << STR.front() << " & " << STR.back() << endl;

	STR.front() = 'x'; STR.back() = 'y';
	cout << "replace the first and last char of STR: " << STR.front() << " & " << STR.back() << endl;

	cout << "-------------------------------" << endl;

	cout << "Rebuild STR2 word by word (x2): ";
	MyString STR3 = "";
	for (int i = 0; i < STR2.getSize(); i++)
		STR3.push_back(STR2[i]);
	//cout << STR3;
	//STR3.clear();
	//STR3 = STR3 + STR2[0] + STR2[1] + STR2[2] + STR2[3];
	cout << STR3 << endl;

	cout << STR3 << " is equal to " << STR2 << "? " << (STR3 == STR2) << endl;
	STR3 = STR3 + "-ZZZ";
	cout << STR3 << " is equal to " << STR2 << "? " << (STR3 == STR2) << endl;

	STR3.pop_back();
	STR3.pop_back();
	cout << "STR3 pop 2 char = " << STR3 << endl;

	STR3.clear();
	cout << "STR3 clear all char = " << STR3 << endl;

	cout << "-------------------------------" << endl;

	cout << "Current STR3 [size=" << STR3.getSize() << ", capacity=" << STR3.getCapacity() << "]" << endl;

	cout << "STR3 append STR2 = " << STR3.append(STR2);
	cout << " [size=" << STR3.getSize() << ", capacity=" << STR3.getCapacity() << "]" << endl;

	STR3.reserve(20);
	cout << "STR3 reserve to 20 = " << STR3 << endl;
	cout << " [size=" << STR3.getSize() << ", capacity=" << STR3.getCapacity() << "]" << endl;

	STR3.shrink_to_fit();
	cout << "STR3 shrink_to_fit = " << STR3 << endl;
	cout << " [size=" << STR3.getSize() << ", capacity=" << STR3.getCapacity() << "]" << endl;

	STR3.resize(25, 'c');
	cout << "STR3 resize to 25 = " << STR3 << endl;
	cout << " [size=" << STR3.getSize() << ", capacity=" << STR3.getCapacity() << "]" << endl;
	cout << "STR3_123 = " << STR3[1] << STR3[2] << STR3[3] << endl;

	system("pause");
	return 0;
}