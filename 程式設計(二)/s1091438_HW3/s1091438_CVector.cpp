#include <iostream>
#include "s1091438_CVector.h"
using namespace std;

ostream& operator<<(ostream& output, const CVector& vec){
	for (size_t i = 0; i < vec.size; i++){
		output << vec[i];
	}
	return output;
};

CVector::CVector(){
	size = 0;
	capacity = 10;
	sPtr = new char[capacity];
};
// Constructs an empty container for character, with a length of zero characters. 
// *default capacity = 10

CVector::CVector(const CVector& vec){
	size = vec.size;
	capacity = vec.capacity;
	sPtr = new char[capacity];
	for (size_t i = 0; i < capacity; i++){
		sPtr[i] = vec.sPtr[i];
	}
};
// Constructs a copy of "vec". (copy constructor)

CVector::~CVector(){
	delete[] sPtr;
};
// Destroys this container object.
size_t CVector::getSize() const{
	return size;
};
// Returns the number of characters in this container (vector).

void CVector::resize(size_t n, char c){
	if (n > capacity) {
		reserve(n);
	}

	if (n > size){
		for (size_t i = size; i < n; i++) {
			sPtr[i] = c;
		}
	}
	size = n;
};
// Resizes the string to a length of n characters.
// If n is smaller than the current string length,
// the current value is shortened to its first n character and remove the characters beyond the nth character.
// If n is greater than the current string length,
// the current content is extended by inserting at the end as many characters as needed to reach a size of n.
// The new elements are initialized by character c.

size_t CVector::getCapacity() const{
	return capacity;
};
// NOTE: default capacity = 10
// Returns the size of the storage space currently allocated for this container,
// expressed in terms of elements.
// *This capacity is not necessarily equal to the string length. It can be equal or greater, 
// with the extra space allowing the object to optimize its operations when new characters are added to the string.
void CVector::reserve(size_t n){
	if (n > capacity) {
		char* tmp = new char[n];
		for (size_t i = 0; i < size; i++) {
			tmp[i] = sPtr[i];
		}
		delete[]sPtr;
		sPtr = new char[n];
		for (size_t i = 0; i < size; i++){
			sPtr[i] = tmp[i];
	    }
		delete[] tmp;
		capacity = n;
	}
};
// Requests that the capacity to be enough to contain n characters.
// If n is greater than the current string capacity,
// the function causes the container to reallocate its storage increasing its capacity to n.
// Otherwise, the function call does NOT cause a reallocation. (the string capacity is not affected)

void CVector::shrink_to_fit(){
	char *tmp = new char[size];
	for (size_t i = 0; i < size; i++) {
		tmp[i] = sPtr[i];
	}
	delete[]sPtr;
	sPtr = new char[size];
	for (size_t i = 0; i < size; i++) {
		sPtr[i] = tmp[i];
	}
	delete[]tmp;
	capacity = size;
};
// Requests the container to reduce its "capacity" to fit its "size".

void CVector::clear(){
	size_t x = size;
	for (size_t i = 0; i < x; i++) {
		pop_back();
	}
};
// Erases the contents of the string, which becomes an empty string 
// (with a length of 0 characters, the Capacity is not affected).

bool CVector::empty() const{
	if (size == 0) {
		return true;
	}
	else {
		return false;
	}
};	
// Returns whether the string is empty (i.e. whether its size is 0).

char& CVector::front(){
	return sPtr[0];
};
// *Returns a reference to the first character of the string.
// This function shall not be called on empty strings.

char& CVector::back(){
	return sPtr[size - 1];
};
// *Returns a reference to the last character of the string.
// This function shall not be called on empty strings.

void CVector::push_back(char c){
	if (size >= capacity){
		reserve(capacity + 1);
	}

	sPtr[size] = c;
	size++;
};
// Appends character c to the end of the string, increasing its length by one.
// *Return void or the reference of itself

void CVector::pop_back(){
	sPtr[size] = '\0';
	size--;
};
// Erases the last character of the string, effectively reducing its size by one. 
// (the string capacity is not affected)
// *Return void or the reference of itself

char& CVector::operator[] (size_t pos){
	return sPtr[pos];
};
//Get character of this string

char CVector::operator[] (size_t pos) const{
	return  sPtr[pos];
};
// Value with the position of a character within the string.
// Note: The first character in a string is denoted by a value of 0 (not 1).
// size_t is an unsigned integral type (the same as member type string::size_type).

bool CVector::operator==(const CVector& str) const{
	int count = 0;
	if (size != str.size) {
		return false;
	}
	else {
		for (size_t i = 0; i < size; i++) {
			if (sPtr[i] == str[i]) {
				count++;
			}
		}
		if (count == size) {
			return true;
		}
		else {
			return false;
		}
	}
};
//< (equal to) true: two identical String
bool CVector::operator!=(const CVector& str) const{
	int count = 0;
	if (size != str.size) {
		return true;
	}
	else {
		for (size_t i = 0; i < size; i++) {
			if (sPtr[i] == str[i]) {
				count = 1;
			}
		}
		if (count == 1) {
			return true;
		}
		else {
			return false;
		}
	}
};
//< (not equal to)
//Compares the value of the string object to the sequence of characters specified by its arguments.

