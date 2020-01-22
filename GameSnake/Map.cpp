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

void Map::initWalls() {
    for (int curPoint = 0; curPoint < width; curPoint++) {
        mainWalls.push_back(Point2d(curPoint, 0));
        mainWalls.push_back(Point2d(curPoint,height - 1));
    }
    for (int curPoint = 1; curPoint < height - 1; curPoint++) {
        mainWalls.push_back(Point2d(0, curPoint));
        mainWalls.push_back(Point2d(width - 1, curPoint));
    }
}

const std::vector<Point2d>& Map::getMainWalls() const {
    return mainWalls;
}

const std::vector<Point2d>& Map::getAdditionWalls() const {
    return additionWalls;
}

void Map::addMainWall(const Point2d& newWall) {
    mainWalls.push_back(newWall);
}

void Map::addAdditionWall(const Point2d& newWall) {
    additionWalls.push_back(newWall);
}