#ifndef PG2CVector_H
#define PG2CVector_H
#include <iostream>
using namespace std;

class CVector
{
	friend ostream &operator<<(ostream& output, const CVector& vec);

public:

	CVector();
	// Constructs an empty container for character, with a length of zero characters. 
	// *default capacity = 10

	CVector(const CVector &vec);
	// Constructs a copy of "vec". (copy constructor)

	~CVector();
	// Destroys this container object.

	size_t getSize() const;
	// Returns the number of characters in this container (vector).

	void resize(size_t n, char c = '\0');
	// Resizes the string to a length of n characters.
	// If n is smaller than the current string length,
	// the current value is shortened to its first n character and remove the characters beyond the nth character.
	// If n is greater than the current string length,
	// the current content is extended by inserting at the end as many characters as needed to reach a size of n.
	// The new elements are initialized by character c.

	size_t getCapacity() const;
	// NOTE: default capacity = 10
	// Returns the size of the storage space currently allocated for this container,
	// expressed in terms of elements.
	// *This capacity is not necessarily equal to the string length. It can be equal or greater, 
	// with the extra space allowing the object to optimize its operations when new characters are added to the string.

	void reserve(size_t n = 0);
	// Requests that the capacity to be enough to contain n characters.
	// If n is greater than the current string capacity,
	// the function causes the container to reallocate its storage increasing its capacity to n.
	// Otherwise, the function call does NOT cause a reallocation. (the string capacity is not affected)

	void shrink_to_fit();
	// Requests the container to reduce its "capacity" to fit its "size".

	void clear();
	// Erases the contents of the string, which becomes an empty string 
	// (with a length of 0 characters, the Capacity is not affected).

	bool empty() const;
	// Returns whether the string is empty (i.e. whether its size is 0).

	char& front();
	// *Returns a reference to the first character of the string.
	// This function shall not be called on empty strings.

	char& back();
	// *Returns a reference to the last character of the string.
	// This function shall not be called on empty strings.

	void push_back(char c);
	// Appends character c to the end of the string, increasing its length by one.
	// *Return void or the reference of itself

	void pop_back();
	// Erases the last character of the string, effectively reducing its size by one. 
	// (the string capacity is not affected)
	// *Return void or the reference of itself

	char& operator[] (size_t pos); //Get character of this string
	char operator[] (size_t pos) const;
	// Value with the position of a character within the string.
	// Note: The first character in a string is denoted by a value of 0 (not 1).
	// size_t is an unsigned integral type (the same as member type string::size_type).

	bool operator==(const CVector &str) const; //< (equal to) true: two identical String
	bool operator!=(const CVector &str) const; //< (not equal to)
	//Compares the value of the string object to the sequence of characters specified by its arguments.

private:
	size_t size;
	// the number of elements in the string
	// This is the number of actual objects held in the string, which is not necessarily equal to its storage capacity.

	size_t capacity;
	// the size of the storage space currently allocated for the string, expressed in terms of elements.
	// This capacity is not necessarily equal to the string size. It can be equal or greater,
	// with the extra space allowing to accommodate for growth without the need to reallocate on each insertion.

	char *sPtr;
	// points to a dynamically allocated array which is used to store the elements of the string
}; // end class String

#endif

