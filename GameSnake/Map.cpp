#include "Map.h"

const size_t Map::getWidth() const {
    return width;
}

const size_t Map::getHeight() const {
    return height;
}

void Map::setWidth(const size_t width) {
    this->width = width;
}

void Map::setHeight(const size_t height) {
    this->height = height;
}

const std::vector<Point2d>& Map::getWalls() const {
    return walls;
}

void Map::addWall(const Point2d& newWall) {
    walls.push_back(newWall);
}