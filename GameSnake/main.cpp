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

    //������������� ������� ������
    sf::Cursor cursor;
    if (cursor.loadFromSystem(sf::Cursor::Arrow))
        Window.setMouseCursor(cursor);

    bool GameStarted = false;
    //�������� ������� ���� �� ��� ���, ���� �� ������ ����
    while (!GameStarted) {
        
        
        unsigned short int answer = MainMenu(Window);   //����� �������� ����
        switch (answer) {
            case 0: { 
                return 0;
                Window.close();
            }
            case 1: {
                //��� ������ ���������� ��������� ����
                GameStarted = true;
                break;
            }
            case 2: {
                if (!CoopMenu(Window)) GameStarted = false;
                break;
            }
            case 3: {
                //��� �������� ����� ���� ��������
                break;
            }
        }

    }
}