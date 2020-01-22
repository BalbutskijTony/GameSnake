#pragma once
#include <list>

#include "Point2d.h"

#define DEFAULT_SNAKE_SIZE 3

enum class AppleType
{
	NO_BONUS = 0,
	SPEED_UP = 1,
	SPEED_DOWN = 2,
	DELETE_HALF = 3,
	ADD_10_APPLE = 4,
	MAX_VALUE = 4
};


class Player
{
public:
	Player();
	Player(const Point2d& startPosition, const Point2d& startDirection);
	~Player() = default;

	const Point2d& getDirection() const;
	void setDirection(const Point2d& newDirection);

	const std::list<Point2d>& getBody() const;
	
	bool getAlive() const;
	void setAlive(const bool isAlive);

	void move();
	void addSegment();

	void addAbility(const AppleType newAbylity);
	const AppleType* getAbilites() const;
	bool dropAbility(const int index);

	bool getIsPlayerMove() const;
	void setIsPlayerMove(const bool isMove);
private:
	Point2d direction;
	std::list<Point2d> body;
	AppleType abilites[6] = { AppleType::NO_BONUS, AppleType::NO_BONUS, AppleType::NO_BONUS,
							AppleType::NO_BONUS, AppleType::NO_BONUS, AppleType::NO_BONUS };
	bool isAlive = true;
	bool isPlyerMove = false;
};

