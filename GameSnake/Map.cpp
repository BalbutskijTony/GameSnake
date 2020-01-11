#include "Map.h"

const size_t Map::getWidth() const {
    return _width;
}

const size_t Map::getHeight() const {
    return _height;
}

void Map::setWidth(const size_t width) {
    _width = width;
}

void Map::setHeight(const size_t height) {
    _height = height;
}