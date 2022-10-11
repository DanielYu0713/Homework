#pragma once
#include <iostream>
#include<string>
using namespace std;

template<typename T>
class CVector
{
	template<typename T>
	friend istream &operator>>(istream& input, CVector<T>& vec);
	template<typename T>
	friend ostream &operator<<(ostream& output, const CVector<T>& vec);
public:

	CVector();
	CVector(const CVector &vec);
	~CVector() {
		delete[] sPtr;
	};
	size_t getSize() const {
		return size;
	};
	void resize(int n, T c = '\0');
	size_t getCapacity() const {
		return capacity;

	};
	void reserve(int n = 0);
	void shrink_to_fit();

	void clear();
	bool empty() const;
	char& front() {
		return sPtr[0];
	};

	char& back() {
		return sPtr[size - 1];
	};
	void push_back(T c);

	void pop_back();

	T& operator[] (int pos) {
		return sPtr[pos];
	};
	T operator[] (int pos) const {
		return sPtr[pos];
	};
	static void check(T vec);
	bool operator==(const CVector<T> &str) const;
	bool operator!=(const CVector<T> &str) const;

private:
	size_t size;
	size_t capacity;
	T *sPtr;
};

template<typename T>
ostream& operator<<(ostream& output, const CVector<T>& vec) {
	if (vec.getSize() % 3 == 0) {
		for (size_t i = 0; i < vec.getSize(); i++) {
			if (i % 3 == 0 && i != 0) {
				output << "¡@";
			}
			output << vec[i];
		}
	}
	else if (vec.getSize() % 3 == 1) {
		for (size_t i = 0; i < vec.getSize(); i++) {
			if (i % 3 == 1) {
				output << "¡@";
			}
			output << vec[i];
		}
	}
	else if (vec.getSize() % 3 == 2) {
		for (size_t i = 0; i < vec.getSize(); i++) {
			if (i % 3 == 2) {
				output << "¡@";
			}
			output << vec[i];
		}
	}
	return output;
};

template<typename T>
istream& operator>>(istream& input, CVector<T>& vec) {
	string s;
	try {
		getline(cin, s);
		for (int i = 0; i < s.size(); i++) {
			if (s[i] != ' ') {
			CVector<T>::check(s[i]);
			vec.push_back(s[i] - '0');
		    }
		}
	}
	catch (bad_cast message) {
		cout << message.what() << endl;
	}

	return input;
}

template<typename T>
void CVector<T>::check(T s) {
	int a = s - '0';
		if (a >= 0 && a <= 9) {

		}
		else {
		  throw bad_cast();
		}
};

template<typename T>
CVector<T>::CVector() {
	size = 0;
	capacity = 100;
	sPtr = new T[capacity];

};

template<typename T>
CVector<T>::CVector(const CVector<T>& vec) {
	size = vec.size;
	capacity = vec.capacity;
	sPtr = new T[capacity];
	for (size_t i = 0; i < capacity; i++) {
		sPtr[i] = vec.sPtr[i];
	}
};

template<typename T>
void CVector<T>::resize(int n, T c) {
	if (n > capacity) {
		reserve(n);
	}

	if (n > size) {
		for (size_t i = size; i < n; i++) {
			sPtr[i] = c;
		}
	}
	size = n;
};

template<typename T>
void CVector<T>::reserve(int n) {
	if (n > capacity) {
		T* tmp = new T[n];
		for (size_t i = 0; i < size; i++) {
			tmp[i] = sPtr[i];
		}
		delete[]sPtr;
		sPtr = new T[n];
		for (size_t i = 0; i < size; i++) {
			sPtr[i] = tmp[i];
		}
		delete[] tmp;
		capacity = n;
	}
};

template<typename T>
void CVector<T>::shrink_to_fit() {
	char *tmp = new T[size];
	for (size_t i = 0; i < size; i++) {
		tmp[i] = sPtr[i];
	}
	delete[]sPtr;
	sPtr = new T[size];
	for (size_t i = 0; i < size; i++) {
		sPtr[i] = tmp[i];
	}
	delete[]tmp;
	capacity = size;
};


template<typename T>
void CVector<T>::clear() {
	T x = size;
	for (size_t i = 0; i < x; i++) {
		pop_back();
	}
};

template<typename T>
bool CVector<T>::empty() const {
	if (size == 0) {
		return true;
	}
	else {
		return false;
	}
};

template<typename T>
void CVector<T>::push_back(T c) {
	if (size >= capacity) {
		reserve(capacity + 1);
	}
	sPtr[size] = c;
	size++;
};

template<typename T>
void CVector<T>::pop_back() {
	sPtr[size] = '\0';
	size--;
};

template<typename T>
bool CVector<T>::operator==(const CVector<T>& str) const {
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

template<typename T>
bool CVector<T>::operator!=(const CVector<T>& str) const {
	int count = 0;
	if (size != str.size) {
		return true;
	}
	else {
		for (size_t i = 0; i < size; i++) {
			count = 0;
			if (sPtr[i] == str[i]) {
				count = 1;
			}
		}
		if (count == 1) {
			return false;
		}
		else {
			return true;
		}
	}
};

class BigNUM : public CVector<int> {

public:
	BigNUM() :CVector<int>() {};
	BigNUM(const BigNUM& str) :CVector<int>(str) {
		*this = str;
	};
	BigNUM(string file);
	BigNUM operator+(const BigNUM& str)const;
	BigNUM operator-(const BigNUM& str)const;
	BigNUM operator*(const BigNUM& str)const;
	BigNUM& operator=(const BigNUM& str);
	bool operator>(const BigNUM& right);
	bool operator<=(const BigNUM& right);
	bool operator>=(const BigNUM& r);
	static void Swap(BigNUM& A, BigNUM& B);
	BigNUM operator+(const string&str);
	BigNUM operator/(const BigNUM& right)const;
	BigNUM operator%(const BigNUM& right)const;
	static BigNUM GCD(const BigNUM& A, const BigNUM& B);
	static BigNUM LCM(const BigNUM&A, const BigNUM&B);
};


