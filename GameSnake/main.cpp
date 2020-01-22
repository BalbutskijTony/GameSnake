#include <vector>
#include <chrono>
#include <future> 
#include <thread>

#include "Map.h"
#include <Windows.h>
#include "MainMenu.h"
#include "UtilityFunctions.h"
#include "CoopMenu.h"
#include <SFML/Window.hpp>
#include "Painter.h"
#include "main.h"

using  namespace sf;

//TODO Singleton

int main() {

    sf::RenderWindow Window(VideoMode(1920, 1080), "Snake the Game", sf::Style::Fullscreen);
    Utility::set(Window);

    //Устанавливаем простой курсор
    sf::Cursor cursor;
    if (cursor.loadFromSystem(sf::Cursor::Arrow))
        Window.setMouseCursor(cursor);

    Window.clear();

    PauseMenu(Window, true);
    PauseMenu(Window, false);

    Texture SnakeSkinTexture;
    SnakeSkinTexture.loadFromFile("images/Snake.png");
    Sprite SnakeHead(SnakeSkinTexture), SnakeBody(SnakeSkinTexture), SnakeAngle(SnakeSkinTexture),  SnakeTail(SnakeSkinTexture);
    SnakeHead.setTextureRect(sf::IntRect(0, 0, 64, 64));
    SnakeBody.setTextureRect(sf::IntRect(64, 0, 64, 64));
   /* SnakeAngle.setTextureRect(sf::IntRect(0, 0, 64, 64));
    SnakeTail.setTextureRect(sf::IntRect(0, 0, 64, 64));
    */

    SnakeHead.setPosition(0, 150);
    SnakeBody.setPosition(0, 0);

    
    while (!Keyboard::isKeyPressed(Keyboard::Escape)) { 
        Window.draw(SnakeHead); 
        Window.draw(SnakeBody);
        Window.display();
    }
    //sf::Text text;
    //sf::Font font;
    //font.loadFromFile("fonts/Jungle Land.ttf");
    //text.setPosition(0, 0);
    //// select the font
    //text.setFont(font); // font is a sf::Font

    //// set the string to display
    //text.setString("192.11.22..4.43.4.23432");

    //// set the character size
    //text.setCharacterSize(50); // in pixels, not points!

    //// set the color
   

    //// set the text style
    //text.setStyle(sf::Text::Bold);

    //Window.display();

    
    //    LoadingAnimation(Window, trunc(Utility::windowParam.x * 0.70), trunc(Utility::windowParam.y * 0.70), (float)-0.01); 
    //     text.setFillColor(sf::Color::Red);
    //    if (Mouse::isButtonPressed(Mouse::Left) && MouseOnSprite(Window, text)){ text.setFillColor(sf::Color::Green);
    //    }
    //    Window.draw(text);
    //    Window.display();
    //}

    


    bool GameStarted = false;
    //Вызываем главное меню до тех пор, пока не начнем игру
    while (!GameStarted) {
        unsigned short int  MManswer = MainMenu(Window);   //вызов Главного меню

        switch (MManswer) {
            case 0: { 
                Window.close();
                return 0;
            }
            case 2: {
                //Тут должна вызываться одиночная игра
                GameStarted = true;
                break;
            }
            case 3: {
                //Меню сетевой игры
                int tmp = CoopMenu(Window);
                /*if (tmp = 1) HostMenu(Window);
                else if (tmp = 2) SearchMenu(Window);*/
                break;
            }
            case 4: {
                //Тут возможно будет меню настроек
                break;
            }
        }

    }

    return 0;
}