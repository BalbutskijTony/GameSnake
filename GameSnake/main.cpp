#include <vector>
#include <chrono>
#include <future> 

#include "Map.h"
#include "Menu.h"
#include "Painter.h"


void gameTic(Player& player) {
    player.move();
}


int main()
{
    RenderWindow MenuWindow(VideoMode(1080, 720), "MENU", sf::Style::Fullscreen);
    unsigned short int answer = MenuFunc(MenuWindow);//вызов меню
    return 0;

    sf::RenderWindow window(sf::VideoMode(1024, 512), "SFML Snake");
    Map map(64, 32);
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
        }
        // TODO: Переделать
        // TODO: Разобраться в чём отличие wait_for от wait_until
        std::future<void> nextTic = std::async([&player] { gameTic(player); });
        nextTic.wait_for(std::chrono::seconds(1));
        window.clear();
        painter.drawGrid(map, window);
        painter.drawPlayer(player, map, window);
        window.display();

        endGameTic = std::chrono::steady_clock::now();
        std::this_thread::sleep_until(startGameTic + std::chrono::seconds(1));
    }
    return 0;
}