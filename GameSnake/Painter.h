#pragma once
#include "Map.h"
#include "Player.h"
#include <SFML/Graphics.hpp>

class Painter
{
public:
    void drawGrid(const Map& map, sf::RenderWindow& window) const;
    void drawMap(const Map& map, sf::RenderWindow& window) const;
    void drawWalls(const Map& map, sf::RenderWindow& window) const;
    void drawPlayer(const Player& player, const Map& map, sf::RenderWindow& window) const;
    void drawPlayer(const Point2d* player, size_t size, const Map& map, sf::RenderWindow& window) const;
    void drawApples(const std::list<std::pair<Point2d, AppleType>>& apples, const Map& map, sf::RenderWindow& window) const;
private:
};

