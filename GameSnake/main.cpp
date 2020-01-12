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
    for (auto wall : map.getWalls())
        if (wall == newPoint) return false;
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

bool isCollide(const Map& map, const Player& player) {
    for (auto curSegment = ++player.getBody().begin(); curSegment != player.getBody().end(); ++curSegment)
        if (*curSegment == *player.getBody().begin()) return true;
    for (auto curWall = map.getWalls().begin(); curWall != map.getWalls().end(); ++curWall)
        if(*curWall == *player.getBody().begin()) return true;
    return false;
}

void initWalls(Map& map) {
    for (int curPoint = 1; curPoint < map.getWidth() - 1; curPoint++) {
        map.addWall(Point2d(curPoint, 0));
        map.addWall(Point2d(curPoint, map.getHeight() - 1));
    }
    for (int curPoint = 1; curPoint < map.getHeight() - 1; curPoint++) {
        map.addWall(Point2d(0, curPoint));
        map.addWall(Point2d(map.getWidth() - 1, curPoint));
    }
    map.addWall(Point2d(0, 0));
    map.addWall(Point2d(0, map.getHeight() - 1));
    map.addWall(Point2d(map.getWidth() - 1, 0));
    map.addWall(Point2d(map.getWidth() - 1, map.getHeight() - 1));
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
    initWalls(map);
    std::list<Point2d> apples;
    Painter painter;
    Player player;
    sf::Event event;
    bool isGame = true;

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
                // �������� ������� ������� - ��������� ��������������� ��������
                if (event.key.code == sf::Keyboard::Escape) window.close();
                if (isGame) {
                    if (event.key.code == sf::Keyboard::Left) move(player, Point2d(-1, 0));
                    if (event.key.code == sf::Keyboard::Right) move(player, Point2d(1, 0));
                    if (event.key.code == sf::Keyboard::Up) move(player, Point2d(0, -1));
                    if (event.key.code == sf::Keyboard::Down) move(player, Point2d(0, 1));
                }
            }
        }
        // TODO: ����������
        // TODO: ����������� � ��� ������� wait_for �� wait_until
        if (isGame) {
            std::future<void> nextTic = std::async([&player, &map, &apples] { gameTic(map, player, apples); });
            nextTic.wait_for(std::chrono::milliseconds(100));
            window.clear();
            painter.drawGrid(map, window);
            painter.drawPlayer(player, map, window);
            painter.drawApples(apples, map, window);
            painter.drawWalls(map, window);
            window.display();

            if (isCollide(map, player)) isGame = false;
            endGameTic = std::chrono::steady_clock::now();
            std::this_thread::sleep_until(startGameTic + std::chrono::milliseconds(100));
        }

        
    }
    return 0;
}