#pragma once
#include <vector>
#include "Point2d.h"

class Map
{
	public:
    // Размеры карты в ячейках
    Map(const size_t width, const size_t height) : width(width), height(height) {};
    ~Map() = default;
    
    const size_t getWidth() const;
    const size_t getHeight() const;

    void setWidth(const size_t width);
    void setHeight(const size_t height);

    const std::vector<Point2d>& getWalls() const;
    void addWall(const Point2d& newWall);
private:
    size_t width;
    size_t height;

    std::vector<Point2d> walls;
};

