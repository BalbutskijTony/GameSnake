#include <vector>
#include <chrono>
#include <future> 

#include "Map.h"
#include "Painter.h"


int generateRandInt(const int from, const int to) {
    return from + (rand() % static_cast<int>(to - from + 1));
}

bool isPointFree(const Map& map, const Player& player, const std::list<Point2d>& apples, const Point2d& newPoint) {
    bool result = true;
    for (auto curPoint : player.getBody())
        if (curPoint == newPoint) return false;
    for (auto curApple : apples)
        if (curApple == newPoint) return false;
    return true;
}

Point2d createNewApple(const Map& map, const Player& player, const std::list<Point2d>& apples) {
    Point2d apple(generateRandInt(0, map.getWidth()), generateRandInt(0, map.getHeight()));

    while (!isPointFree(map, player, apples, apple)) {
        apple.x = generateRandInt(0, map.getWidth());
        apple.y = generateRandInt(0, map.getHeight());
    }

    return apple;
}


void gameTic(const Map& map, Player& player, std::list<Point2d>& apples) {
    
    Point2d head = player.getBody().front() + player.getDirection();
    bool isEatAppleNow = false;
    for(auto apple : apples)
        if (head == apple) {
            player.addSegment();
            apples.remove(apple);
            isEatAppleNow = true;
            break;
        }
    if(!isEatAppleNow) player.move();

    if(apples.size() < 1/**/)
        apples.push_back(createNewApple(map, player, apples));

}


void /*Game*/ move(Player& player, const Point2d& newDirection) {
    int scalaMult = newDirection * player.getDirection();
    if (scalaMult < 0) return; // Incorrect action
    if (scalaMult > 0) return; // No action
    player.setDirection(newDirection);
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(1024, 512), "SFML Snake");
    Map map(64, 32);
    std::list<Point2d> apples;
    Painter painter;
    Player player;
    sf::Event event;

    std::chrono::time_point<std::chrono::steady_clock> startGameTic, endGameTic;
    


    while (window.isOpen())
    {
        startGameTic = std::chrono::steady_clock::now();
       
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            
            if (event.type == sf::Event::KeyPressed)
            {
                // Получаем нажатую клавишу - выполняем соответствующее действие
                if (event.key.code == sf::Keyboard::Escape) window.close();
                if (event.key.code == sf::Keyboard::Left) move(player, Point2d(-1, 0));
                if (event.key.code == sf::Keyboard::Right) move(player, Point2d(1, 0));
                if (event.key.code == sf::Keyboard::Up) move(player, Point2d(0, -1));
                if (event.key.code == sf::Keyboard::Down) move(player, Point2d(0, 1));

            }
        }
        // TODO: Переделать
        // TODO: Разобраться в чём отличие wait_for от wait_until
        std::future<void> nextTic = std::async([&player, &map, &apples] { gameTic(map, player, apples); });
        nextTic.wait_for(std::chrono::milliseconds(500));
        window.clear();
        painter.drawGrid(map, window);
        painter.drawPlayer(player, map, window);
        painter.drawApples(apples, map, window);
        window.display();

        endGameTic = std::chrono::steady_clock::now();
        std::this_thread::sleep_until(startGameTic + std::chrono::milliseconds(500));
    }
    return 0;
}