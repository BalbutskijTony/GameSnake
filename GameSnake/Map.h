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

    void initWalls();

    const std::vector<Point2d>& getMainWalls() const;
    const std::vector<Point2d>& getAdditionWalls() const;
    void addMainWall(const Point2d& newWall);
    void addAdditionWall(const Point2d& newWall);
private:
    size_t width;
    size_t height;

    std::vector<Point2d> mainWalls;
    std::vector<Point2d> additionWalls;
};

