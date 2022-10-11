#include <iostream>
#include <cstring>
#include "s1091438_MyString.h"
using namespace std;

MyString::MyString() :CVector() {};
// Constructs an empty string, with a length of zero characters. 
// *default capacity = 10

MyString::MyString(const MyString& str): CVector(str){
	*this = str;
};
// Constructs a copy of "str". (copy constructor)

MyString::MyString(const MyString& str, size_t pos, size_t len): CVector(){
	if (str.getSize() - pos - 1 <= len || len >= msize) {
		len = str.getSize() - 1;
	}
	for (size_t i = pos; i <= pos + len; i++) {
		push_back(str[i]);
	}
};
// Copies the portion of str that begins at the character position "pos" and spans "len" characters 
// (or until the end of str, if either str is too short or if len is string::msize).
MyString::MyString(const char* s):CVector(){
	for (size_t i = 0; i < strlen(s); i++) {
		push_back(s[i]);
	}
};
// Copies the array of character (C-string) pointed by s.
// The char *s is a pointer to a null-terminated sequence of characters. (all following char* are the same/)
// The sequence is copied as the new value for the string.
MyString::~MyString() {};	
// Destroys the string object.

MyString& MyString::append(const MyString& str){
	size_t t = getSize() + str.getSize();
	reserve(t);

	size_t thisSize = getSize();
	for (size_t i = thisSize; i < t; i++) {
		push_back(str[i - thisSize]);
	}
	return *this;
};
// Appends a str on the tail of current MyString. 
// *Return the reference of itself

MyString MyString::substr(size_t pos, size_t len) const{
	MyString str;
	for (size_t i = pos; i < pos + len; i++) {
		str.push_back(operator[](i));
	}
	return str;
};
// The substring is the portion of the object that starts at character position pos and spans len characters 
// (or until the end of the string, whichever comes first).
// *Returns a newly constructed string object with its value initialized to a copy of a substring of this object.

MyString& MyString::insert(size_t pos, const MyString& str){
	size_t Size2 = getSize() + str.getSize();
	reserve(Size2);

	MyString tmp;
	for (size_t i = pos; i < getSize(); i++) {
		tmp.push_back(operator[](i));
	}
	resize(pos);//複製保存後，再把插入的位置後面刪除

	for (size_t i = pos; i < pos+str.getSize(); i++){
		push_back(str[i - pos]);
	}
	for (size_t i = pos + str.getSize(); i < Size2; i++) {
		push_back(tmp[i - pos - str.getSize()]);
	}
	return *this;
};
// Inserts a copy of a str at "pos".
// example: str = "to be question", str2 = "the "
// str.insert(6,str2); 
// = to be (the )question = to be the question
// *Return the reference of itself

MyString& MyString::insert(size_t pos, const MyString& str, size_t subpos, size_t sublen)
{
	size_t strSize;
	if (subpos + sublen > str.getSize()) {
		strSize = str.getSize();
	}
	else {
		strSize = sublen;
	}
	size_t Size2 = getSize() + strSize;
	reserve(Size2);

	MyString tmp;
	for (size_t i = pos; i < getSize() + pos; i++) {
		tmp.push_back(operator[](i));
	}
	resize(pos);//複製保存後，再把插入的位置後面刪除

	for (size_t i = pos; i < pos+strSize ; i++){
	    push_back(str[i - pos + subpos]);//從subpos 到strSize
	}
	for (size_t i = pos + strSize; i < Size2; i++) {
		push_back(tmp[i-pos-strSize]);
	}
	return *this;
};
// Inserts a copy of a substring of str at "pos". The substring is the portion of "str" that
// begins at the character position subpos and spans sublen characters (or until the end of str).
// example: str = "to be the question", str3 = "or not to be"
// str.insert(6,str3,3,4); // to be (not )the question
// *Return the reference of itself

MyString& MyString::erase(size_t subpos, size_t sublen)
{
	MyString tmp;
	for (size_t i = subpos + sublen; i < getSize(); i++) {
		tmp.push_back(operator[](i));
	}//將要刪除後面的字預存起來 ex:存"String"
	resize(subpos);//ex:刪掉str後所有字,MystrString -> My
	for (size_t i = 0; i < tmp.getSize(); i++) {
		push_back(tmp[i]);
	}

	return *this;
};
// Erases the portion of the string value that begins at the character position pos and spans len characters 
// (or until the end of the string, if either the content is too short or if len is string::msize.)
// *Return the reference of itself

size_t MyString::find(const MyString& str, size_t pos) const{
	for (size_t i = 0; i < getSize() ; i++){
		bool exist = true;
		for (size_t j = 0; j < str.getSize(); j++){
			if (operator[](i + j) != str[j]){
				exist = false;
				break;
			}
		}
		if (exist == true) {
			return i;
		}
	}
	return msize;
};
// Searches the portion of the string value that begins at the character position "pos" until the end of the string
// for the first occurrence of the string str.
// Return Value: The position of the first character of the first match. If no matches were found, the function returns MyString::msize.

size_t MyString::find_first_of(const MyString& str, size_t pos) const{
	for (size_t i = 0; i < getSize(); i++){
		for (size_t j = 0; j < str.getSize(); j++){
			if (operator[](i) == str[j]){
				return i;
			}
		}
	}
	return msize;
};
// Searches the portion of the string value that begins at the character position "pos" until the end of the string
// for the first character that matches *any* of the characters of the string str.
// Return Value: The position of the first character that matches. If no matches are found, the function returns MyString::msize.
//Add several operators
MyString MyString::operator+ (const MyString& rhs) const {
	MyString str;
	for (size_t i = 0; i < getSize(); i++) {
		str.push_back(operator[](i));
	}
	for (size_t i = 0; i < rhs.getSize(); i++){
		str.push_back(rhs[i]);
    }
	return str;
};

MyString MyString::operator+ (const char* rhs) const{
	MyString str;
	for (size_t i = 0; i < getSize(); i++) {
		str.push_back(operator[](i));
	}
	for (size_t i = 0; i < strlen(rhs); i++) {
		str.push_back(rhs[i]);
	}
	return str;
};

MyString operator+ (const char* lhs, const MyString& rhs) {
	MyString str;
	for (size_t i = 0; i < strlen(lhs); i++) {
		str.push_back(lhs[i]);
	}
	for (size_t i = 0; i < rhs.getSize(); i++){
		str.push_back(rhs[i]);
    }
	return str;
};
// Returns a newly constructed string object with its value 
// being the *concatenation* of the characters in lhs followed by those of rhs.
// Note: If of type char*, it shall point to a null-terminated character sequence.

MyString& MyString::operator= (const MyString& str) {
	resize(0);
	for (size_t i = 0; i < str.getSize(); i++){
		push_back(str[i]);
    }
		return *this;
};

MyString& MyString::operator= (const char* s){
	resize(0);
	for (size_t i = 0; i < strlen(s); i++) {
		push_back(s[i]);
	}
	return *this;
};