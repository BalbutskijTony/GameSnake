#include <SFML/Graphics.hpp>
#include <vector>
#include <list>
#include <chrono>

int mapLength = 64;
int mapWidth = 32;

class Snake {
public:
    Snake() = delete;
    Snake(const int startX, const int startY, const size_t snakeSize = 3);
    ~Snake();
    const std::list<std::pair<int, int>>& getData();

    void setDimention(std::pair<int, int> dimention);
    const std::pair<int, int>& getDimention() const;

    void iterate();
private:
    std::list<std::pair<int, int>> data;
    std::pair<int, int> dimention;
};

Snake::Snake(const int startX, const int startY, const size_t snakeSize = 3) {
    dimention = { 1, 0 };

    for (int i = 0; i < snakeSize; i++) {
        data.push_back({ startX + dimention.first * i, startY + dimention.second * i });
    }
}

Snake::~Snake() {
}

const std::list<std::pair<int, int>>& Snake::getData() {
    return data;
}

void Snake::setDimention(std::pair<int, int> dimention) {
    this->dimention = dimention;
}

const std::pair<int, int>& Snake::getDimention() const {
    return dimention;
}

void Snake::iterate() {
    data.push_back({ data.back().first + dimention.first, data.back().second + dimention.second });
    data.erase(data.begin());
}


void waitTimePoint(const std::chrono::time_point<std::chrono::system_clock>& timePoint) {
    while (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - timePoint).count() < 0);
}


int main()
{
    sf::RenderWindow window(sf::VideoMode(1024, 512), "SFML Snake");
    int nodeLength = 1024 / mapLength;
    int nodeWidth = 512 / mapWidth;
    std::list<sf::RectangleShape> snake;
    
    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();
    //
    end = std::chrono::system_clock::now();

    int elapsed_seconds = std::chrono::duration_cast<std::chrono::seconds>
        (end - start).count();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        for (auto a : snake) {
            window.draw(a);
        }
        window.display();
    }

    return 0;
}