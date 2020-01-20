#include <vector>
#include <chrono>
#include <future> 

#include "Game.h"
#include "Painter.h"



int main()
{
    sf::RenderWindow window(sf::VideoMode(1024, 512), "SFML Snake");
    Map map(64, 32);
    map.initWalls();
    
    Painter painter;
    
    Game newGame(map);
    int curPlayerIndex = newGame.addNewPlayer(Player(Point2d(5, 5), Point2d(1, 0)));
    

    sf::Event event;
    bool isGame = true;
    bool isPlayerMove = false;

    std::chrono::time_point<std::chrono::steady_clock> startGameTic, endGameTic;
    

    while (window.isOpen())
    {
        startGameTic = std::chrono::steady_clock::now();
        isPlayerMove = false;
        while (window.pollEvent(event))
        {
            
            if (event.type == sf::Event::Closed)
                window.close();
            
            if (event.type == sf::Event::KeyPressed)
            {
                // Получаем нажатую клавишу - выполняем соответствующее действие
                if (event.key.code == sf::Keyboard::Escape) window.close();
                if (isGame) {
                    if (event.key.code == sf::Keyboard::Left && !isPlayerMove) {
                        if(newGame.setNewDirection(curPlayerIndex, Point2d(-1, 0)))
                            isPlayerMove = true;
                    }
                    if (event.key.code == sf::Keyboard::Right && !isPlayerMove) {
                        if (newGame.setNewDirection(curPlayerIndex, Point2d(1, 0)))
                            isPlayerMove = true;
                    }
                    if (event.key.code == sf::Keyboard::Up && !isPlayerMove) {
                        if (newGame.setNewDirection(curPlayerIndex, Point2d(0, -1)))
                            isPlayerMove = true;
                    }
                    if (event.key.code == sf::Keyboard::Down && !isPlayerMove) {
                        if (newGame.setNewDirection(curPlayerIndex, Point2d(0, 1)))
                            isPlayerMove = true;
                    }
                }
            }
        }
        // TODO: Переделать
        // TODO: Разобраться в чём отличие wait_for от wait_until
        if (isGame) {
            std::future<void> nextTic = std::async([&newGame] { newGame.gameTic(); });
            nextTic.wait_for(std::chrono::milliseconds(200));
            window.clear();
            painter.drawGrid(map, window);
            painter.drawPlayer(newGame.getPlayer(curPlayerIndex), newGame.getMap(), window);
            painter.drawApples(newGame.getApples(), newGame.getMap(), window);
            painter.drawWalls(newGame.getMap(), window);
            window.display();

            if (newGame.isPlayerCollide(curPlayerIndex)) isGame = false;
            endGameTic = std::chrono::steady_clock::now();
            std::this_thread::sleep_until(startGameTic + std::chrono::milliseconds(200));
        }

        
    }
    return 0;
}