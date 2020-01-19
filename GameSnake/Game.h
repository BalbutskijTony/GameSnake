#pragma once
#include "Map.h"
#include "Player.h"

#ifdef DEBUG
#include <iostream>
#endif 

class Game
{
public:
    void setNewMap(const Map& newMap);
    const Map& getMap() const;

    const std::list<std::pair<Point2d, AppleType>>& getApples() const;
    const size_t getCountApples() const;
    const Point2d createNewApple() const;

    // return player index. if == -1 error
    const int addNewPlayer(const Player& newPlayer);
    bool isPlayerAlive(const int playerIndex) const;

    bool setNewDirection(const int playerIndex, const Point2d& newDirection);

    bool isPlayerCollide(const int playerIndex) const;
    void initWalls(/*Map& map*/);// ->Map
    void gameTic(/*const Map& map,*/ /*Player& player,*/ /*std::list<Point2d>& apples*/);
    void move(Player& player, const Point2d& newDirection);//->private
private:
    bool isPointFree(const Point2d& newPoint) const;
    const int generateRandInt(const int from, const int to) const;
    std::vector<Player> players;
    std::list<std::pair<Point2d, AppleType>> apples;
    Map map;
};

