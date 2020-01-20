#include <vector>
#include <chrono>
#include <future> 

#include "Map.h"
#include "MainMenu.h"
#include "CoopMenu.h"
#include "Painter.h"

using  namespace sf;

//Включить множественное нажатие перед игрой

int main() {

    RenderWindow Window(VideoMode(1920, 1080), "Snake the Game", sf::Style::Fullscreen);

    //Устанавливаем простой курсор
    sf::Cursor cursor;
    if (cursor.loadFromSystem(sf::Cursor::Arrow))
        Window.setMouseCursor(cursor);
    //
    Window.EnableKeyRepeat(false);

    bool GameStarted = false;
    //Вызываем главное меню до тех пор, пока не начнем игру
    while (!GameStarted) {
        
        unsigned short int answer = MainMenu(Window);   //вызов Главного меню
        switch (answer) {
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
                if CoopMenu(Window);
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