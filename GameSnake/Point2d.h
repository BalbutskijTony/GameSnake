#pragma once
class Point2d
{
public:
	Point2d() = default;
	Point2d(int x, int y) : x(x), y(y) {};
	Point2d(const Point2d& right) = default;
	Point2d(Point2d&& right) = default;
	int x;
	int y;

	const Point2d& operator=(const Point2d& right);
	Point2d operator+(const Point2d& right) const;
	Point2d operator*(const int right) const;
};

