#pragma once
#include "Map.h"
#include <SFML/Graphics.hpp>

class Painter
{
public:
    void drawGrid(const Map& map, sf::RenderWindow& window) const;
    void drawMap(const Map& map, sf::RenderWindow& window) const;
private:
};

