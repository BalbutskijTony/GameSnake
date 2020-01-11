#include <vector>
#include <list>
#include <chrono>

#include "Map.h"
#include "Painter.h"
////Painter
//class Painter {

//};
//

//


int main()
{
    sf::RenderWindow window(sf::VideoMode(1024, 512), "SFML Snake");
    Map map(64, 32);
    Painter painter;
    

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        painter.drawGrid(map, window);
        window.display();
    }
    return 0;
}