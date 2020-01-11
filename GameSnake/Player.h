#pragma once
#include <list>

#include "Point2d.h"

#define DEFAULT_SNAKE_SIZE 3

class Player
{
public:
	Player();
	~Player() = default;

	const Point2d& getDirection() const;
	void setDirection(const Point2d& newDirection);

	const std::list<Point2d>& getBody() const;
	
	void move();
	void addSegment();
private:
	Point2d direction;
	std::list<Point2d> body;
};

