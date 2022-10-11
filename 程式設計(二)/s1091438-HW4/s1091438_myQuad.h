#pragma once
#include <iostream>
#include <string>
#include "s1091438_myPoint2.h"
using namespace std;

class myQuadrilateral{
	friend ostream& operator<<(ostream& output, myQuadrilateral& vec);
public:

	myQuadrilateral(int, int, int, int, int, int, int, int);
	Point2 P1() ;
	Point2 P2() ;
	Point2 P3() ;
	Point2 P4();
	void print();
	virtual double getArea();
	virtual string getType();
	virtual bool isValid();

protected:
	Point2 p1, p2, p3, p4;
};

class myTrapezium : public myQuadrilateral{
public:
	myTrapezium(int, int, int, int, int, int, int, int);
	virtual double getArea();
	string getType();
	bool isValid();
};

class myParallelogram : public myQuadrilateral{
public:
	myParallelogram(int, int, int, int, int, int, int, int);
	virtual double getArea();
	virtual string getType();
	virtual bool isValid();
};

class myRectangle : public myParallelogram{
public:
	myRectangle(int, int, int, int, int, int, int, int);
	virtual double getArea();
	virtual string getType();
	virtual bool isValid();
};

class mySquare : public myRectangle{
public:
	mySquare(int, int, int, int, int, int, int, int);
	virtual double getArea();
	virtual string getType();
	virtual bool isValid();
};

