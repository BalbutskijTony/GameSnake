#include <vector>
#include <chrono>
#include <future> 

#include "Map.h"
#include "MainMenu.h"
#include "CoopMenu.h"
#include "Painter.h"


int main()
{
    RenderWindow Window(VideoMode(1280, 720), "Snake the Game", sf::Style::Close);

    //Устанавливаем простой курсор
    sf::Cursor cursor;
    if (cursor.loadFromSystem(sf::Cursor::Arrow))
        Window.setMouseCursor(cursor);

    bool GameStarted = false;
    //Вызываем главное меню до тех пор, пока не начнем игру
    while (!GameStarted) {
        
        
        unsigned short int answer = MainMenu(Window);   //вызов Главного меню
        switch (answer) {
            case 0: { 
                return 0;
                Window.close();
            }
            case 1: {
                //Тут должна вызываться одиночная игра
                GameStarted = true;
                break;
            }
            case 2: {
                if (!CoopMenu(Window)) GameStarted = false;
                break;
            }
            case 3: {
                //Тут возможно будет меню настроек
                break;
            }
        }

    }
}