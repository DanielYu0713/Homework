#include <iostream>
#include <cmath>
#include "s1091438_myPoint2.h"

using namespace std;

ostream& operator<<(ostream& output, const Point2& p){
	output << "(" << p.getX() << "," << p.getY() << ")";
	return output;
};


Point2::Point2(const int x1, const int y1) : x(x1), y(y1) {}; //x = x1, y = y1


Point2::Point2(const Point2& p){
	x = p.x;
	y = p.y;
};//copy

const int Point2::getX() const{
	return x;
};

const int Point2::getY() const{
	return y;
};

double Point2::getDistance(const Point2&P1, const Point2&P2) {
	double t = sqrt((P1.x - P2.x)*(P1.x - P2.x) + (P1.y - P2.y)*(P1.y - P2.y));
	return t;
};
bool Point2::isParallel(const Point2& A, const Point2& B, const Point2& C, const Point2& D){
	if (A.getX() - B.getX() == 0 && C.getX() - D.getX() == 0) {
		return true; //鉛直線,分母 = 0,與下方分開寫
	}
	else if (A.getX() - B.getX() == 0 || C.getX() - D.getX() == 0) {
		return false;
	}
	else{
		if ((double) ( (A.getY() - B.getY()) / (A.getX() - B.getX()) ) == (double) ( (C.getY() - D.getY()) / (C.getX() - D.getX()) )) {
			return true;
		}    //斜率
		else {
			return false;
		}
	}
};

bool Point2::isVertical(const Point2& A, const Point2& B, const Point2& C){
	if ((A.getX() - B.getX())*(C.getX() - B.getX()) + (A.getY() - B.getY())*(C.getY() - B.getY()) == 0) {
		return true;
	}
	else {
		return false;
	}
};//向量內積 = 0