#pragma once
#include "Map.h"
#include "Player.h"

#undef DEBUG
#ifdef DEBUG
#include <iostream>
#endif 

class Game
{
public:
    Game(const Map& map);
    ~Game() = default;

    void setNewMap(const Map& newMap);
    const Map& getMap() const;

    const std::list<std::pair<Point2d, AppleType>>& getApples() const;
    const size_t getCountApples() const;
    const Point2d createNewApple() const;

    // return player index. if == -1 error
    const int addNewPlayer(const Player& newPlayer);
    bool isPlayerAlive(const int playerIndex) const;

    const Player& getPlayer(const int playerIndex) const;
    const std::vector<Player>& getAllPlayers() const;

    bool setNewDirection(const int playerIndex, const Point2d& newDirection);
    void setIsPlayerMove(const int playerIndex, const bool isMove);
    void setAlive(const int playerIndex, const bool isAlive);

    bool isPlayerCollide(const int playerIndex) const;
    virtual void gameTic();
protected:
    bool isPointFree(const Point2d& newPoint) const;
    const int generateRandInt(const int from, const int to) const;
    std::vector<Player> players;
    std::list<std::pair<Point2d, AppleType>> apples;
    Map map;
};

