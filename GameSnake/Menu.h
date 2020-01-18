#pragma once
#include <iostream>
#include <Windows.h>
#include "Math.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>


//TODO Доделать кнопки в сетевой
//TODO Настроить вывод списка серверов текстом
//TODO Договориться о возвращаемых кодах
//TODO Общая оптимизация и раскидать по функциям

#define PreScaleX 1280 //Стандартные настройки окна
#define PreScaleY 720
using namespace sf;


unsigned short int MenuFunc(RenderWindow& window) {
	
	Vector2u windowParam = window.getSize(); //Берем настройки окна
	std::cout << windowParam.x << ' ' << windowParam.y << std::endl;
	
	Vector2f scale((float)windowParam.x/PreScaleX, (float)windowParam.y/PreScaleY); //Получаем параметры для растяжения картинок на экране
	std::cout << scale.x << ' ' << scale.y;
	
	sf::Cursor cursor; //Устанавливаем простой курсор
	if (cursor.loadFromSystem(sf::Cursor::Arrow)) 
		window.setMouseCursor(cursor);
	
	Texture SoloGameTexture, MultiGameTexture, SettingsTexture, ExitTexture, MMBackgroundTexture; //Текстуры для главного меню
	SoloGameTexture.loadFromFile("images/SoloGameBt.png");
	MultiGameTexture.loadFromFile("images/MultiplayerBt.png");
	SettingsTexture.loadFromFile("images/SettingsBt.png");
	ExitTexture.loadFromFile("images/ExitBt.png");
	MMBackgroundTexture.loadFromFile("images/MainmenuBg.jpg");
	Sprite SoloButton(SoloGameTexture), MultiplayerButton(MultiGameTexture), ExitButton(ExitTexture), SettingsButton(SettingsTexture), MainMenuBg(MMBackgroundTexture);

	Texture MPBackgroundTexture; //Текстуры для меню мультиплеера
	MPBackgroundTexture.loadFromFile("images/MultiplayerBg.jpg");
	Sprite MultiPlayerBg(MPBackgroundTexture);

	Texture SettingsBackgroundTexture; //Текстуры для настроек
	SettingsBackgroundTexture.loadFromFile("images/SettingsBg.jpg");
	Sprite SettingsBg(SettingsBackgroundTexture);

	Texture YesTexture, NoTexture, SureTexture; //Текстуры для подтверждения о выходе
	YesTexture.loadFromFile("images/YesBt.png");
	NoTexture.loadFromFile("images/NoBt.png");
	SureTexture.loadFromFile("images/SureBt.png");
	Sprite YesButton(YesTexture), NoButton(NoTexture), SureQuestion(SureTexture);

	Texture ReturnToMainmenuTexture; //Текстуры для кнопки возврата в главное меню
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
	YesButton.setPosition(trunc(windowParam.x * 0.3), trunc(windowParam.y * 0.60));
	SureQuestion.setPosition(trunc(windowParam.x * 0.25), trunc(windowParam.y * 0.4));
	ReturnMMButton.setPosition(trunc(windowParam.x * 0.75), trunc(windowParam.y * 0.75));
	
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

			if (SoloButton.getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y)) {
				SoloButton.setColor(Color::Green);
			}
			if (MultiplayerButton.getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y)) {
				MultiplayerButton.setColor(Color::Green);
			}
			if (SettingsButton.getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y)) {
				SettingsButton.setColor(Color::Green);
			}
			if (ExitButton.getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y)) {
				ExitButton.setColor(Color::Red);
			}

			if (Mouse::isButtonPressed(Mouse::Left) && SoloButton.getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y)) {
				//Начало игры
				menuNum = 2;
			}
			if (Mouse::isButtonPressed(Mouse::Left) && MultiplayerButton.getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y)) {
				//Переход в сетевую игру
				menuNum = 3;
			}
			if (Mouse::isButtonPressed(Mouse::Left) && SettingsButton.getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y)) {
				menuNum = 4;
			}
			if (Mouse::isButtonPressed(Mouse::Left) && ExitButton.getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y)) {
				//
				menuNum = 0;
			}
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
			MultiPlayerBg.setColor(Color::White);
			ReturnMMButton.setColor(Color::White);
			if (Mouse::isButtonPressed(Mouse::Left) && ReturnMMButton.getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y)) {
				menuNum = 1;
			}
			if (ReturnMMButton.getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y)) {
				ReturnMMButton.setColor(Color::Red);
			}
			window.draw(MultiPlayerBg);
			window.draw(ReturnMMButton);
		}
		//Меню 4 - настройки
		if (menuNum == 4) {
			ReturnMMButton.setColor(Color::White);
			if (Mouse::isButtonPressed(Mouse::Left) && ReturnMMButton.getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y)) {
				menuNum = 1;
			}
			if (ReturnMMButton.getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y)) {
				ReturnMMButton.setColor(Color::Red);
			}
			window.draw(SettingsBg);
			window.draw(ReturnMMButton);
		}

		//Условия выхода
		if (menuNum == 0 || Keyboard::isKeyPressed(Keyboard::Escape)){
			YesButton.setColor(Color::White);
			NoButton.setColor(Color::White);
			if (YesButton.getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y)) {
				YesButton.setColor(Color::Red);
			}
			if (NoButton.getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y)) {
				NoButton.setColor(Color::Green);
			}
			if (Mouse::isButtonPressed(Mouse::Left) && YesButton.getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y)) {
				window.close();
				return 0;
			}
			if (Mouse::isButtonPressed(Mouse::Left) && NoButton.getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y)) {
				menuNum = 1;
			}
			window.draw(NoButton);
			window.draw(YesButton);
			window.draw(SureQuestion);
		}
		if (event.type == sf::Event::Closed) {
			window.close();
			return 0;
		}
		window.display();
	}
}
