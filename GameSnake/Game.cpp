#include "Game.h"


const int Game::generateRandInt(const int from, const int to) const  {
    return from + (rand() % static_cast<int>(to - from + 1));
}

void Game::setNewMap(const Map& newMap) {
    map = newMap;
}

const Map& Game::getMap() const {
    return map;
}

const std::list<std::pair<Point2d, AppleType>>& Game::getApples() const {
    return apples;
}

const size_t Game::getCountApples() const {
    return apples.size();
}

const Point2d Game::createNewApple() const {
    Point2d apple(generateRandInt(0, map.getWidth()), generateRandInt(0, map.getHeight()));

    while (!isPointFree(apple)) {
        apple.x = generateRandInt(0, map.getWidth());
        apple.y = generateRandInt(0, map.getHeight());
    }
    return apple;
}

bool Game::isPointFree(const Point2d& newPoint) const {
    bool result = true;
    for (auto curPlayer : players) {
        if (curPlayer.getAlive()) {
            for (auto curPoint : curPlayer.getBody())
                if (curPoint == newPoint) return false;
        }
    }
    for (auto curApple : apples)
        if (curApple.first == newPoint) return false;
    for (auto wall : map.getMainWalls())
        if (wall == newPoint) return false;
    for (auto wall : map.getAdditionWalls())
        if (wall == newPoint) return false;
    return true;
}

// return player index. if == -1 error
const int Game::addNewPlayer(const Player& newPlayer) {
    players.push_back(newPlayer);
    return players.size() - 1;
}

bool Game::isPlayerAlive(const int playerIndex) const {
    return players[playerIndex].getAlive();
}

bool Game::setNewDirection(const int playerIndex, const Point2d& newDirection) {
    int scalarMult = players[playerIndex].getDirection() * newDirection;
#ifdef DEBUG
    std::cout << "Old direction: " << players[playerIndex].getDirection().x << ", " << players[playerIndex].getDirection().y << std::endl;
    std::cout << "New direction: " << newDirection.x << ", " << newDirection.y << std::endl;
    std::cout << "Scalar: " << scalarMult << std::endl;
    if (scalarMult < 0) std::cout << "return false" << std::endl;
    else if (scalarMult > 0) std::cout << "return true" << std::endl;
    else std::cout << "Set new direction. return true" << std::endl;
#endif
    if (scalarMult < 0) return false;
    if (scalarMult > 0) return true;
    players[playerIndex].setDirection(newDirection);
    return true;
}

bool Game::isPlayerCollide(const int playerIndex) const {
    auto player = players[playerIndex];
    for (auto curSegment = ++player.getBody().begin(); curSegment != player.getBody().end(); ++curSegment)
        if (*curSegment == *player.getBody().begin()) return true;
    for (auto curWall = map.getMainWalls().begin(); curWall != map.getMainWalls().end(); ++curWall)
        if (*curWall == *player.getBody().begin()) return true;
    for (auto curWall = map.getAdditionWalls().begin(); curWall != map.getAdditionWalls().end(); ++curWall)
        if (*curWall == *player.getBody().begin()) return true;
    for (int otherPlayerInd = 0; otherPlayerInd < players.size(); otherPlayerInd++)
        if (otherPlayerInd != playerIndex) {
            auto otherPlayer = players[otherPlayerInd];
            for (auto curSegment = otherPlayer.getBody().begin(); curSegment != otherPlayer.getBody().end(); ++curSegment)
                if (*curSegment == *player.getBody().begin()) return true;
        }
    return false;
}


void Game::gameTic() {
    for (auto &player : players) {
        Point2d head = player.getBody().front() + player.getDirection();
        bool isEatAppleNow = false;
        for (auto apple : apples)
            if (head == apple.first) {
                player.addSegment();
                player.addAbility(apple.second);
                apples.remove(apple);
                isEatAppleNow = true;
                break;
            }
        if (!isEatAppleNow) player.move();
    }

    int curCountPlayers = 0;
    for (int i = 0; i < players.size(); i++) {
        if (players[i].getAlive()) {
            curCountPlayers++;
            //players[i].move();
        }
    }

    while(apples.size() < curCountPlayers)
        apples.push_back({ createNewApple(), static_cast<AppleType>(generateRandInt(0, static_cast<int>(AppleType::MAX_VALUE))) });
}


Game::Game(const Map& map) : map(map) {
}

const Player& Game::getPlayer(const int playerIndex) const {
    return players[playerIndex];
}

const std::vector<Player>& Game::getAllPlayers() const {
    return players;
}

void Game::setIsPlayerMove(const int playerIndex, const bool isMove) {
    players[playerIndex].setIsPlayerMove(isMove);
}

void Game::setAlive(const int playerIndex, const bool isAlive) {
    players[playerIndex].setAlive(isAlive);
}