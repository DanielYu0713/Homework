#pragma once
#include <iostream>
using namespace std;

class Point2{
	friend ostream& operator<<(ostream& output, const Point2& p);
public:
	Point2(const int x ,const int y);
	Point2(const Point2& p);
	const int getX() const;
	const int getY() const;
	static double getDistance(const Point2&, const Point2&);
	static bool isParallel(const Point2& A, const Point2& B, const Point2& C, const Point2& D);
	static bool isVertical(const Point2& A, const Point2& B, const Point2& C);
private:
	int x = 0;
	int y = 0;
};

