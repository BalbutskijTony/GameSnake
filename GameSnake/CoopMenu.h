#pragma once

#include "MainMenu.h"

#define PreScaleX 1280
#define PreScaleY 720

using namespace sf;

unsigned short int CoopMenu(RenderWindow& window) {
	
	//Берем настройки окна
	Vector2u windowParam = window.getSize();
	std::cout << windowParam.x << ' ' << windowParam.y << std::endl;

	//Получаем параметры для растяжения картинок на экране
	Vector2f scale((float)windowParam.x / PreScaleX, (float)windowParam.y / PreScaleY);
	std::cout << scale.x << ' ' << scale.y;

	//Текстуры для меню мультиплеера
	Texture MPBackgroundTexture, MPHostTexture, MPSearchTexture;
	MPSearchTexture.loadFromFile("images/SearchBt.png");
	MPHostTexture.loadFromFile("images/CreateServerBt.png");
	MPBackgroundTexture.loadFromFile("images/MultiplayerBg.jpg");
	Sprite MultiPlayerBg(MPBackgroundTexture), CreateServerButton(MPHostTexture), SearchButton(MPSearchTexture);

	//Текстуры для кнопки возврата в главное меню
	Texture ReturnToMainmenuTexture;
	ReturnToMainmenuTexture.loadFromFile("images/ReturnBt.png");
	Sprite ReturnMMButton(ReturnToMainmenuTexture);

	//Растягиваем спрайты под окно
	MultiPlayerBg.setScale(scale.x, scale.y);
	CreateServerButton.setScale(scale.x, scale.y);
	SearchButton.setScale(scale.x, scale.y);
	ReturnMMButton.setScale(scale.x*0.5, scale.y*0.5);

	//Настраиваем положение кнопок в меню
	CreateServerButton.setPosition(trunc(windowParam.x * 0.05), trunc(windowParam.y * 0.05));
	SearchButton.setPosition(trunc(windowParam.x * 0.05), trunc(windowParam.y * 0.25));
	ReturnMMButton.setPosition(trunc(windowParam.x * 0.75), trunc(windowParam.y * 0.90));

	//Фоновый спрайт
	MultiPlayerBg.setPosition(0,0);

	int menuNum = 1;
	sf::Event event;
	while (window.waitEvent(event)) {
		CreateServerButton.setColor(Color::White);
		SearchButton.setColor(Color::White);
		ReturnMMButton.setColor(Color::White);

		//Изменение цвета при наведении указателя
		if (MouseOnSprite(window, CreateServerButton))
			CreateServerButton.setColor(Color::Green);
		else if (MouseOnSprite(window, SearchButton))
			SearchButton.setColor(Color::Green);
		else if (MouseOnSprite(window, ReturnMMButton))
			ReturnMMButton.setColor(Color::Red);

		//Поведение при нажании мыши
		if (Mouse::isButtonPressed(Mouse::Left) && MouseOnSprite(window, CreateServerButton)) //Переход к запуску хоста
			return 1;
		else if (Mouse::isButtonPressed(Mouse::Left) && MouseOnSprite(window, SearchButton)) //Переход к поиску хостов
			return 2;
		else if (Mouse::isButtonPressed(Mouse::Left) && MouseOnSprite(window, ReturnMMButton)) //Переход к диалогу выхода
			return 0;

		//Нажатие на esc
		if (Keyboard::isKeyPressed(Keyboard::Escape)) return 0;

		window.draw(MultiPlayerBg);
		window.draw(CreateServerButton);
		window.draw(SearchButton);
		window.draw(ReturnMMButton);

		window.display();
	}
}