#include <iostream>
#include<math.h>
#include "s1091438_myQuad.h"
#include "s1091438_myPoint2.h"

using namespace std;

ostream& operator<<(ostream& output, myQuadrilateral& vec){
	output << vec.getType() << endl;
	output << vec.P1() << endl << vec.P2() << endl << vec.P3() << endl << vec.P4() ;
	return output;
};
myQuadrilateral::myQuadrilateral(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4) : p1(x1, y1), p2(x2, y2), p3(x3, y3), p4(x4, y4) {};

Point2 myQuadrilateral::P1() {
	return p1;
}; //get Point1,p1(x1,y1)

Point2 myQuadrilateral::P2() {
	return p2;
};

Point2 myQuadrilateral::P3() {
	return p3;
};

Point2 myQuadrilateral::P4() {
	return p4;
};

void myQuadrilateral::print(){
	cout << getType() << endl;
	cout << P1() << endl << P2() << endl << P3() << endl << P4();
};

double myQuadrilateral::getArea(){
	double area = (p1.getX() * p4.getY() + p4.getX() * p3.getY() + p3.getX() * p2.getY() + p2.getX() * p1.getY() - p4.getX() * p1.getY() - p3.getX() * p4.getY() - p2.getX() * p3.getY() - p1.getX() * p2.getY()) / 2;
	return area;
};

string myQuadrilateral::getType(){
	string str = "Quadrilateral";
	return str;
};

bool myQuadrilateral::isValid(){
	if (p1.getX() == p2.getX() && p1.getY() == p2.getY() || p1.getX() == p3.getX() && p1.getY() == p3.getY() || p1.getX() == p4.getX() && p1.getY() == p4.getY() || p2.getX() == p3.getX() && p2.getY() == p3.getY() || p2.getX() == p4.getX() && p2.getY() == p4.getY() || p3.getX() == p4.getX() && p3.getY() == p4.getY()) {
		return false;
	}
	else if ((p2.getY() - p1.getY())*(p3.getX() - p1.getX()) - (p3.getY() - p1.getY())*(p2.getX() - p1.getX()) == 0 ||
		    (p3.getY() - p1.getY())*(p4.getX() - p1.getX()) - (p4.getY() - p1.getY())*(p3.getX() - p1.getX()) == 0 ||
		    (p2.getY() - p1.getY())*(p4.getX() - p1.getX()) - (p4.getY() - p1.getY())*(p2.getX() - p1.getX()) == 0 ||
		    (p3.getY() - p2.getY())*(p4.getX() - p2.getX()) - (p4.getY() - p2.getY())*(p3.getX() - p2.getX()) == 0) 
	{
		return false;
	}
	else {
		return true;
	}
	
};//沒有三點共線以及無相同的點,用向量觀念寫的

myTrapezium::myTrapezium(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4) : myQuadrilateral(x1, y1, x2, y2, x3, y3, x4, y4) {};

double myTrapezium::getArea() {
	double area = 0.5*abs((p1.getX() - p2.getX())*(p3.getY() - p2.getY()) - (p3.getX() - p2.getX())*(p1.getY() - p2.getY())) +
		          0.5*abs((p1.getX() - p4.getX())*(p3.getY() - p4.getY()) - (p3.getX() - p4.getX())*(p1.getY() - p4.getY()));
	 return area;
 };//向量解,將梯形切成兩個三角形

 string myTrapezium::getType(){
	string str = myQuadrilateral::getType() + "-Trapezium";
	return str;
};

bool myTrapezium::isValid(){
	if (myQuadrilateral::isValid() == false) {
		return false;
	}
	else if (Point2::isParallel(P1(), P2(), P3(), P4()) == false && Point2::isParallel(P2(), P3(), P4(), P1()) == true) {
		return true;
	}//只能有一邊平行
	else if (Point2::isParallel(P1(), P2(), P3(), P4()) == true && Point2::isParallel(P2(), P3(), P4(), P1()) == false) {
		return true;
	}
	else {
		return false;
	}
};

myParallelogram::myParallelogram(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4) : myQuadrilateral(x1, y1, x2, y2, x3, y3, x4, y4) {};

double myParallelogram::getArea() {
	double area = abs((p2.getX() - p1.getX())*(p4.getY() - p1.getY()) - (p4.getX() - p1.getX())*(p2.getY() - p1.getY()));
	return area;
};//向量解

string myParallelogram::getType(){
	string str = myQuadrilateral::getType() + "-Parallelogram";
	return str;
};

bool myParallelogram::isValid(){
	if (myQuadrilateral::isValid() == false) {
		return false;
	}

	else if (Point2::isParallel(P1(), P2(), P3(), P4()) == false || Point2::isParallel(P2(), P3(), P4(), P1()) == false) {
		return false;
	}

	else {
		return true;
	}
};

myRectangle::myRectangle(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4) : myParallelogram(x1, y1, x2, y2, x3, y3, x4, y4) {};

double myRectangle::getArea() {
	double area = Point2::getDistance(P1(), P2())*Point2::getDistance(P2(), P3());
	return area;
};

string myRectangle::getType(){
	string str = myParallelogram::getType() + "-Rectangle";
	return str;
};

bool myRectangle::isValid(){
	if (myParallelogram::isValid() == false) {
		return false;
	}

	else if (Point2::isVertical(P1(), P2(), P3()) == false || Point2::isVertical(P3(), P4(), P1()) == false) {
		return false;
	}//角度要是90度,因為平行,檢查兩個角就好

	else {
		return true;
	}
};

mySquare::mySquare(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4) : myRectangle(x1, y1, x2, y2, x3, y3, x4, y4) {};

double mySquare::getArea() {
	double area = pow(Point2::getDistance(P1(), P2()), 2);
	return area;
};

string mySquare::getType(){
	string str = myRectangle::getType() + "-Square";
	return str;
};

bool mySquare::isValid(){
	if (myRectangle::isValid() == false) {
		return false;
	}

	else if (Point2::getDistance(P1(), P2()) != Point2::getDistance(P2(), P3())
		|| Point2::getDistance(P2(), P3()) != Point2::getDistance(P3(), P4())
		|| Point2::getDistance(P3(), P4()) != Point2::getDistance(P4(), P1())
		|| Point2::getDistance(P4(), P1()) != Point2::getDistance(P1(), P2()))
	{
		return false;
	}//任兩邊要相等
	else {
		return true;
	}
};