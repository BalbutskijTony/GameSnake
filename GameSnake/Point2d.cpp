#include "Point2d.h"
const Point2d& Point2d::operator=(const Point2d& right) {
	x = right.x;
	y = right.y;
	return *this;
}

Point2d Point2d::operator+(const Point2d& right) const {
	return Point2d(x + right.x, y + right.y);
}

Point2d Point2d::operator*(const int right) const {
	return Point2d(x * right, y * right);
}