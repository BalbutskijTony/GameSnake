#include "Painter.h"

void Painter::drawGrid(const Map& map, sf::RenderWindow& window) const {
    double stepByX = static_cast<double>(window.getSize().x) / map.getWidth();
    double stepByY = static_cast<double>(window.getSize().y) / map.getHeight();

    for (size_t col = 0; col <= map.getWidth(); col++) {
        sf::Vertex line[] =
        {
            sf::Vertex(sf::Vector2f(static_cast<double>(col)* stepByX, 0)),
            sf::Vertex(sf::Vector2f(static_cast<double>(col)* stepByX, window.getSize().y))
        };

        
        window.draw(line, 2, sf::Lines);
    }

    for (size_t row = 0; row <= map.getHeight(); row++) {
        sf::Vertex line[] =
        {
            sf::Vertex(sf::Vector2f(0, static_cast<double>(row)* stepByY)),
            sf::Vertex(sf::Vector2f(window.getSize().x, static_cast<double>(row)* stepByY))
        };

        window.draw(line, 2, sf::Lines);
    }
}

void Painter::drawMap(const Map& map, sf::RenderWindow& window) const {

}