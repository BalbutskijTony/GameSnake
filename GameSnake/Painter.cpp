#include "Painter.h"

void Painter::drawGrid(const Map& map, sf::RenderWindow& window) const {
    float stepByX = static_cast<float>(window.getSize().x) / map.getWidth();
    float stepByY = static_cast<float>(window.getSize().y) * 0.9 / map.getHeight();

    for (size_t col = 0; col <= map.getWidth(); col++) {
        sf::Vertex line[] =
        {
            sf::Vertex(sf::Vector2f(static_cast<float>(col)* stepByX, 0)),
            sf::Vertex(sf::Vector2f(static_cast<float>(col)* stepByX, stepByY * map.getHeight()))
        };

        
        window.draw(line, 2, sf::Lines);
    }

    for (size_t row = 0; row <= map.getHeight(); row++) {
        sf::Vertex line[] =
        {
            sf::Vertex(sf::Vector2f(0, static_cast<float>(row)* stepByY)),
            sf::Vertex(sf::Vector2f(window.getSize().x, static_cast<float>(row)* stepByY))
        };

        window.draw(line, 2, sf::Lines);
    }
}

void Painter::drawMap(const Map& map, sf::RenderWindow& window) const {

}

void Painter::drawPlayer(const Player& player, const Map& map, sf::RenderWindow& window) {
    float stepByX = static_cast<float>(window.getSize().x) / map.getWidth();
    float stepByY = static_cast<float>(window.getSize().y) * 0.9 / map.getHeight();
    
    for (auto segment : player.getBody()) {
        sf::RectangleShape rectangle(sf::Vector2f(stepByX, stepByY));
        rectangle.move(sf::Vector2f(stepByX * segment.x, stepByY * segment.y));
        rectangle.setFillColor(sf::Color::Green);
        window.draw(rectangle);
    }
}

void Painter::drawApples(const std::list<std::pair<Point2d, AppleType>>& apples, const Map& map, sf::RenderWindow& window) const {
    float stepByX = static_cast<float>(window.getSize().x) / map.getWidth();
    float stepByY = static_cast<float>(window.getSize().y) * 0.9 / map.getHeight();

    for (auto applePosition : apples) {
        sf::RectangleShape rectangle(sf::Vector2f(stepByX, stepByY));
        rectangle.move(sf::Vector2f(stepByX * applePosition.first.x, stepByY * applePosition.first.y));
        rectangle.setFillColor(sf::Color::Red);
        window.draw(rectangle);
    }
}

void Painter::drawWalls(const Map& map, sf::RenderWindow& window) const {
    float stepByX = static_cast<float>(window.getSize().x) / map.getWidth();
    float stepByY = static_cast<float>(window.getSize().y) * 0.9 / map.getHeight();
    // TODO: draw addition walls
    for (auto wall : map.getMainWalls()) {
        sf::RectangleShape rectangle(sf::Vector2f(stepByX, stepByY));
        rectangle.move(sf::Vector2f(stepByX * wall.x, stepByY * wall.y));
        rectangle.setFillColor(sf::Color::Magenta);
        window.draw(rectangle);
    }
}
