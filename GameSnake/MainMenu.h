#pragma once

#include <iostream>
#include <Windows.h>
#include "Math.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>


//TODO Разобраться с очисткой данных
//TODO Хранить все кнопки для каждого из пунктов в одной текстуре
//TODO Сделать однократное нажатие на мышку


//Проверка положения мышки над спарайтом
bool MouseOnSprite(RenderWindow& window, Sprite sprite) {
	if (sprite.getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y)) return true;
	else return false;
}

unsigned short int MainMenu(RenderWindow& window) {
	
	//Берем настройки окна
	Vector2u windowParam = window.getSize(); 
	std::cout << windowParam.x << ' ' << windowParam.y << std::endl;
	
	//Получаем параметры для растяжения картинок на экране
	Vector2f scale((float)windowParam.x/PreScaleX, (float)windowParam.y/PreScaleY); 
	std::cout << scale.x << ' ' << scale.y;

	//Текстуры для главного меню
	Texture SoloGameTexture, MultiGameTexture, SettingsTexture, ExitTexture, MMBackgroundTexture; 
	SoloGameTexture.loadFromFile("images/SoloGameBt.png");
	MultiGameTexture.loadFromFile("images/MultiplayerBt.png");
	SettingsTexture.loadFromFile("images/SettingsBt.png");
	ExitTexture.loadFromFile("images/ExitBt.png");
	MMBackgroundTexture.loadFromFile("images/MainmenuBg.jpg");
	Sprite SoloButton(SoloGameTexture), MultiplayerButton(MultiGameTexture), ExitButton(ExitTexture), SettingsButton(SettingsTexture), MainMenuBg(MMBackgroundTexture);

	//Текстуры для настроек
	Texture SettingsBackgroundTexture; 
	SettingsBackgroundTexture.loadFromFile("images/SettingsBg.jpg");
	Sprite SettingsBg(SettingsBackgroundTexture);

	//Текстуры для подтверждения о выходе
	Texture YesTexture, NoTexture, SureTexture; 
	YesTexture.loadFromFile("images/YesBt.png");
	NoTexture.loadFromFile("images/NoBt.png");
	SureTexture.loadFromFile("images/SureBt.png");
	Sprite YesButton(YesTexture), NoButton(NoTexture), SureQuestion(SureTexture);

	//Текстуры для кнопки возврата в главное меню
	Texture ReturnToMainmenuTexture; 
	ReturnToMainmenuTexture.loadFromFile("images/ReturnBt.png");
	Sprite ReturnMMButton(ReturnToMainmenuTexture);

	//Другие спрайты 
	
	//Растягиваем спрайты под окно
	SoloButton.setScale(scale.x, scale.y); 
	MultiplayerButton.setScale(scale.x, scale.y);
	SettingsButton.setScale(scale.x, scale.y);
	MainMenuBg.setScale(scale.x, scale.y);
	ExitButton.setScale(scale.x, scale.y);
	ReturnMMButton.setScale(scale.x*0.5, scale.y*0.5);
	YesButton.setScale(scale.x*0.5, scale.y*0.5);
	NoButton.setScale(scale.x * 0.5, scale.y * 0.5);
	SureQuestion.setScale(scale.x, scale.y);
	MultiPlayerBg.setScale(scale.x, scale.y);
	SettingsBg.setScale(scale.x, scale.y);

	//Настраиваем положение кнопок в меню
	SoloButton.setPosition(trunc(windowParam.x * 0.05), trunc(windowParam.y * 0.05));
	MultiplayerButton.setPosition(trunc(windowParam.x * 0.05), trunc(windowParam.y * 0.25));
	SettingsButton.setPosition(trunc(windowParam.x * 0.05), trunc(windowParam.y * 0.45));
	ExitButton.setPosition(trunc(windowParam.x * 0.05), trunc(windowParam.y * 0.75));
	NoButton.setPosition(trunc(windowParam.x * 0.58), trunc(windowParam.y * 0.60));
	YesButton.setPosition(trunc(windowParam.x * 0.33), trunc(windowParam.y * 0.60));
	SureQuestion.setPosition(trunc(windowParam.x * 0.25), trunc(windowParam.y * 0.4));
	ReturnMMButton.setPosition(trunc(windowParam.x * 0.75), trunc(windowParam.y * 0.90));
	
	//Положение фона на страницах
	SettingsBg.setPosition(0, 0);
	MainMenuBg.setPosition(0, 0);
	MultiPlayerBg.setPosition(0, 0);

	
	///////////////////////////////////МЕНЮ///////////////////////////////////
	//0 - выход, 1 - главное меню, 2 - один игрок, 3 - сетевая  4 - настройки
	int menuNum = 1;
	sf::Event event;
	while (window.waitEvent(event))
	{
		//Меню 1
		if (menuNum == 1) {
			SoloButton.setColor(Color::White);
			MultiplayerButton.setColor(Color::White);
			SettingsButton.setColor(Color::White);
			ExitButton.setColor(Color::White);

			//Изменение цвета при наведении указателя
			if (MouseOnSprite(window,SoloButton))
				SoloButton.setColor(Color::Green);
			else if (MouseOnSprite(window, MultiplayerButton))
				MultiplayerButton.setColor(Color::Green);
			else if (MouseOnSprite(window, SettingsButton))
				SettingsButton.setColor(Color::Green);
			else if (MouseOnSprite(window, ExitButton))
				ExitButton.setColor(Color::Red);

			//Поведение при нажании мыши
			if (Mouse::isButtonPressed(Mouse::Left) && MouseOnSprite(window, SoloButton)) //Переход к началу игры
				menuNum = 2;
			else if (Mouse::isButtonPressed(Mouse::Left) && MouseOnSprite(window, MultiplayerButton)) //Переход в меню сетевой игры
				menuNum = 3;
			else if (Mouse::isButtonPressed(Mouse::Left) && MouseOnSprite(window, SettingsButton)) //Переход к меню настроек
				menuNum = 4;
			else if (Mouse::isButtonPressed(Mouse::Left) && MouseOnSprite(window, ExitButton)) //Переход к диалогу выхода
				menuNum = 0;

			//Нажатие на esc
			if (Keyboard::isKeyPressed(Keyboard::Escape)) menuNum = 0;

			window.draw(MainMenuBg);
			window.draw(SoloButton);
			window.draw(MultiplayerButton);
			window.draw(ExitButton);
			window.draw(SettingsButton);
		}

		//Меню 2 - одиночная
		if (menuNum == 2) {
			return 2;
		}
		//Меню 3 - сетевая
		if (menuNum == 3) {
			return 3;
			/*MultiPlayerBg.setColor(Color::White);
			ReturnMMButton.setColor(Color::White);
			if (Mouse::isButtonPressed(Mouse::Left) && ReturnMMButton.getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y)) {
				menuNum = 1;
			}
			if (ReturnMMButton.getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y)) {
				ReturnMMButton.setColor(Color::Red);
			}
			window.draw(MultiPlayerBg);
			window.draw(ReturnMMButton);*/
		}
		//Меню 4 - настройки
		if (menuNum == 4) {

			ReturnMMButton.setColor(Color::White);
			if (MouseOnSprite(window, ReturnMMButton)) {
				ReturnMMButton.setColor(Color::Red);
				if (Mouse::isButtonPressed(Mouse::Left)) //Переход в главное меню
					menuNum = 1;
			}

			//Нажание на esc
			if (Keyboard::isKeyPressed(Keyboard::Escape)) menuNum = 1;

			window.draw(SettingsBg);
			window.draw(ReturnMMButton);
		}

		//Условия выхода
		if (menuNum == 0) {
			YesButton.setColor(Color::White);
			NoButton.setColor(Color::White);

			//Изменение цвета при наведении
			if (MouseOnSprite(window, YesButton))
				YesButton.setColor(Color::Red);
			else if (MouseOnSprite(window, NoButton))
				NoButton.setColor(Color::Green);

			//Поведение при нажатии
			if (Mouse::isButtonPressed(Mouse::Left) && MouseOnSprite(window, YesButton)) {
				return 0;
			}
			else if (Mouse::isButtonPressed(Mouse::Left) && MouseOnSprite(window, NoButton))
				menuNum = 1;

			window.draw(NoButton);
			window.draw(YesButton);
			window.draw(SureQuestion);
		}

		if (event.type == sf::Event::Closed) {
			return 0;
		}

		window.display();
	}
}
