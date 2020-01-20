#include <vector>
#include <chrono>
#include <future> 

#include "Game.h"
#include "Painter.h"

enum class MoveAction
{
    LEFT,
    RIGTH,
    DOWN,
    UP,
    NO_ACTION
};

enum class AbilityAction
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
    std::pair<MoveAction, sf::Keyboard::Key> left;
    std::pair<MoveAction, sf::Keyboard::Key> right;
    std::pair<MoveAction, sf::Keyboard::Key> down;
    std::pair<MoveAction, sf::Keyboard::Key> up;
};

void buttonClickHandler(const std::vector<PlayerController>& controllers, const sf::Keyboard::Key button, Game& game) {
    for (int curPlayerIndex = 0; curPlayerIndex < controllers.size(); curPlayerIndex++) {
        if (button == controllers[curPlayerIndex].left.second && !game.getPlayer(curPlayerIndex).getIsPlayerMove()) {
            if (game.setNewDirection(curPlayerIndex, Point2d(-1, 0))) {
                game.setIsPlayerMove(curPlayerIndex, true);
                return;
            }
        }
        if (button == controllers[curPlayerIndex].right.second && !game.getPlayer(curPlayerIndex).getIsPlayerMove()) {
            if (game.setNewDirection(curPlayerIndex, Point2d(1, 0))) {
                game.setIsPlayerMove(curPlayerIndex, true);
                return;
            }
        }
        if (button == controllers[curPlayerIndex].up.second && !game.getPlayer(curPlayerIndex).getIsPlayerMove()) {
            if (game.setNewDirection(curPlayerIndex, Point2d(0, -1))) {
                game.setIsPlayerMove(curPlayerIndex, true);
                return;
            }
        }
        if (button == controllers[curPlayerIndex].down.second && !game.getPlayer(curPlayerIndex).getIsPlayerMove()) {
            if (game.setNewDirection(curPlayerIndex, Point2d(0, 1))) {
                game.setIsPlayerMove(curPlayerIndex, true);
                return;
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

    controllers[0].down = std::make_pair(MoveAction::DOWN, sf::Keyboard::S);
    controllers[0].left = std::make_pair(MoveAction::LEFT, sf::Keyboard::A);
    controllers[0].right = std::make_pair(MoveAction::RIGTH, sf::Keyboard::D);
    controllers[0].up = std::make_pair(MoveAction::UP, sf::Keyboard::W);

    controllers[1].down = std::make_pair(MoveAction::DOWN, sf::Keyboard::Down);
    controllers[1].left = std::make_pair(MoveAction::LEFT, sf::Keyboard::Left);
    controllers[1].right = std::make_pair(MoveAction::RIGTH, sf::Keyboard::Right);
    controllers[1].up = std::make_pair(MoveAction::UP, sf::Keyboard::Up);



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
                // Получаем нажатую клавишу - выполняем соответствующее действие
                if (event.key.code == sf::Keyboard::Escape) window.close();
                if (isGame) {
                    buttonClickHandler(controllers, event.key.code, newGame);
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