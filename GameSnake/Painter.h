#pragma once
#include "Map.h"
#include "Player.h"
#include <SFML/Graphics.hpp>

class Painter
{
public:
    void drawGrid(const Map& map, sf::RenderWindow& window) const;
    void drawMap(const Map& map, sf::RenderWindow& window) const;
    void drawPlayer(const Player& player, const Map& map, sf::RenderWindow& window) const;
    void drawApples(const std::list<Point2d>& apples, const Map& map, sf::RenderWindow& window) const;
private:
};

