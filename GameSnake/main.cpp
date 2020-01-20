#include <vector>
#include <chrono>
#include <future> 

#include "Game.h"
#include "Painter.h"


enum struct MoveAction
{
    LEFT,
    RIGTH,
    DOWN,
    UP,
    NO_ACTION
};

enum struct AbilityAction
{
    USE_1_ABILITY,
    USE_2_ABILITY,
    USE_3_ABILITY,
    USE_4_ABILITY,
    USE_5_ABILITY,
    USE_6_ABILITY
};

class PlayerController {
public:
    std::pair<sf::Keyboard::Key, Point2d> commands[4];
};

void buttonClickHandler(const std::vector<PlayerController>& controllers, const sf::Keyboard::Key button, Game& game) {
    for (int curPlayerIndex = 0; curPlayerIndex < controllers.size(); curPlayerIndex++) {
        for (int commandIndex = 0; commandIndex < 4; commandIndex++) {
            if (button == controllers[curPlayerIndex].commands[commandIndex].first
                && !game.getPlayer(curPlayerIndex).getIsPlayerMove()) {
                if (game.setNewDirection(curPlayerIndex, controllers[curPlayerIndex].commands[commandIndex].second)) {
                    game.setIsPlayerMove(curPlayerIndex, true);
                    return;
                }
            }
        }
    }
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(1024, 512), "SFML Snake");
    Map map(64, 32);
    map.initWalls();
    
    Painter painter;
    
    Game newGame(map);
    int player1Index = newGame.addNewPlayer(Player(Point2d(5, 5), Point2d(1, 0)));
    int player2Index = newGame.addNewPlayer(Player(Point2d(55, 25), Point2d(-1, 0)));
    
    std::vector<PlayerController> controllers = { PlayerController(), PlayerController() };

    controllers[0].commands[0] = std::make_pair(sf::Keyboard::S, Point2d(0, 1));
    controllers[0].commands[1] = std::make_pair(sf::Keyboard::A, Point2d(-1, 0));
    controllers[0].commands[2] = std::make_pair(sf::Keyboard::D, Point2d(1, 0));
    controllers[0].commands[3] = std::make_pair(sf::Keyboard::W, Point2d(0, -1));

    controllers[1].commands[0] = std::make_pair(sf::Keyboard::Down, Point2d(0, 1));
    controllers[1].commands[1] = std::make_pair(sf::Keyboard::Left, Point2d(-1, 0));
    controllers[1].commands[2] = std::make_pair(sf::Keyboard::Right, Point2d(1, 0));
    controllers[1].commands[3] = std::make_pair(sf::Keyboard::Up, Point2d(0, -1));



    sf::Event event;
    bool isGame = true;
    bool isPlayerMove = false;

    std::chrono::time_point<std::chrono::steady_clock> startGameTic, endGameTic;
    

    while (window.isOpen())
    {
        startGameTic = std::chrono::steady_clock::now();
        for (int curPlayerIndex = 0; curPlayerIndex < controllers.size(); curPlayerIndex++)
            newGame.setIsPlayerMove(curPlayerIndex, false);
        while (window.pollEvent(event))
        {
            
            if (event.type == sf::Event::Closed)
                window.close();
            
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Escape) window.close();
                if (isGame) {
                    buttonClickHandler(controllers, event.key.code, newGame);
                }
            }
        }

        // TODO: Разобраться в чём отличие wait_for от wait_until
        if (isGame) {
            std::future<void> nextTic = std::async([&newGame] { newGame.gameTic(); });
            nextTic.wait_for(std::chrono::milliseconds(200));
            window.clear();
            painter.drawGrid(map, window);
            for(int curPlayerIndex = 0; curPlayerIndex < controllers.size(); curPlayerIndex++)
                if(newGame.getPlayer(curPlayerIndex).getAlive())
                    painter.drawPlayer(newGame.getPlayer(curPlayerIndex), newGame.getMap(), window);
            painter.drawApples(newGame.getApples(), newGame.getMap(), window);
            painter.drawWalls(newGame.getMap(), window);
            window.display();

            isGame = false;
            for (int curPlayerIndex = 0; curPlayerIndex < controllers.size(); curPlayerIndex++) {
                if (newGame.isPlayerCollide(curPlayerIndex)) {
                    newGame.setAlive(curPlayerIndex, false);
                }
                isGame = isGame || newGame.getPlayer(curPlayerIndex).getAlive();
            }
            endGameTic = std::chrono::steady_clock::now();
            std::this_thread::sleep_until(startGameTic + std::chrono::milliseconds(200));
        }

        
    }
    return 0;
}