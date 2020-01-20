#include "Player.h"

Player::Player() {
	direction.x = 0;
	direction.y = 1;

	Point2d startPoint;
	startPoint.x = 1;
	startPoint.y = 1;

	body.emplace_back(startPoint + direction * (DEFAULT_SNAKE_SIZE - 1));
	for (int curSeg = DEFAULT_SNAKE_SIZE - 2; curSeg >= 0; curSeg--)
		body.emplace_back(startPoint + direction * curSeg);
}

const Point2d& Player::getDirection() const {
	return direction;
}

void Player::setDirection(const Point2d& newDirection) {
	direction = newDirection;
}

const std::list<Point2d>& Player::getBody() const {
	return body;
}

void Player::move() {
	body.push_front(body.front() + direction);
	body.pop_back();
}

void Player::addSegment() {
	body.push_front(body.front() + direction);
}

bool Player::getAlive() const {
	return isAlive;
}

void Player::setAlive(const bool isAlive) {
	this->isAlive = isAlive;
}

void Player::addAbility(const AppleType newAbylity) {
	for (int i = 0; i < 6; i++) {
		if (abilites[i] == AppleType::NO_BONUS) {
			abilites[i] = newAbylity;
			return;
		}
	}
}

const AppleType* Player::getAbilites() const {
	return abilites;
}

bool Player::dropAbility(const int index) {
	if (index < 0 || index > 5) return false;
	if (abilites[index] == AppleType::NO_BONUS) return false;
	abilites[index] = AppleType::NO_BONUS;
	return true;
}

Player::Player(const Point2d& startPosition, const Point2d& startDirection) {
	direction = startDirection;

	Point2d startPoint;
	startPoint = startPosition;

	body.emplace_back(startPoint + direction * (DEFAULT_SNAKE_SIZE - 1));
	for (int curSeg = DEFAULT_SNAKE_SIZE - 2; curSeg >= 0; curSeg--)
		body.emplace_back(startPoint + direction * curSeg);
}