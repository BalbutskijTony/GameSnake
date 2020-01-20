#include <vector>
#include <chrono>
#include <future> 

#include "Map.h"
#include "MainMenu.h"
#include "CoopMenu.h"
#include "Painter.h"

using  namespace sf;

//�������� ������������� ������� ����� �����

int main() {

    RenderWindow Window(VideoMode(1920, 1080), "Snake the Game", sf::Style::Fullscreen);

    //������������� ������� ������
    sf::Cursor cursor;
    if (cursor.loadFromSystem(sf::Cursor::Arrow))
        Window.setMouseCursor(cursor);
    //
    Window.EnableKeyRepeat(false);

    bool GameStarted = false;
    //�������� ������� ���� �� ��� ���, ���� �� ������ ����
    while (!GameStarted) {
        
        unsigned short int answer = MainMenu(Window);   //����� �������� ����
        switch (answer) {
            case 0: { 
                Window.close();
                return 0;
            }
            case 2: {
                //��� ������ ���������� ��������� ����
                GameStarted = true;
                break;
            }
            case 3: {
                //���� ������� ����
                if CoopMenu(Window);
                break;
            }
            case 4: {
                //��� �������� ����� ���� ��������
                break;
            }
        }

    }

    return 0;
}