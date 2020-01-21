#pragma once

#include "UtilityFunctions.h"

//TODO Разобраться с очисткой данных
//TODO Хранить все кнопки для каждого из пунктов в одной текстуре
//TODO Сделать однократное нажатие на мышку

using namespace sf;

unsigned short int MainMenu(RenderWindow& window) {
	
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
	
	//Растягиваем спрайты под окно
	SoloButton.setScale(Utility::scale.x, Utility::scale.y);
	MultiplayerButton.setScale(Utility::scale.x, Utility::scale.y);
	SettingsButton.setScale(Utility::scale.x, Utility::scale.y);
	MainMenuBg.setScale(Utility::scale.x, Utility::scale.y);
	ExitButton.setScale(Utility::scale.x, Utility::scale.y);
	ReturnMMButton.setScale(Utility::scale.x*0.5, Utility::scale.y*0.5);
	YesButton.setScale(Utility::scale.x*0.5, Utility::scale.y*0.5);
	NoButton.setScale(Utility::scale.x * 0.5, Utility::scale.y * 0.5);
	SureQuestion.setScale(Utility::scale.x, Utility::scale.y);
	SettingsBg.setScale(Utility::scale.x, Utility::scale.y);

	//Настраиваем положение кнопок в меню
	SoloButton.setPosition(trunc(Utility::windowParam.x * 0.05), trunc(Utility::windowParam.y * 0.05));
	MultiplayerButton.setPosition(trunc(Utility::windowParam.x * 0.05), trunc(Utility::windowParam.y * 0.25));
	SettingsButton.setPosition(trunc(Utility::windowParam.x * 0.05), trunc(Utility::windowParam.y * 0.45));
	ExitButton.setPosition(trunc(Utility::windowParam.x * 0.05), trunc(Utility::windowParam.y * 0.75));
	NoButton.setPosition(trunc(Utility::windowParam.x * 0.58), trunc(Utility::windowParam.y * 0.60));
	YesButton.setPosition(trunc(Utility::windowParam.x * 0.33), trunc(Utility::windowParam.y * 0.60));
	SureQuestion.setPosition(trunc(Utility::windowParam.x * 0.25), trunc(Utility::windowParam.y * 0.4));
	ReturnMMButton.setPosition(trunc(Utility::windowParam.x * 0.75), trunc(Utility::windowParam.y * 0.90));
	
	//Положение фона на страницах
	SettingsBg.setPosition(0, 0);
	MainMenuBg.setPosition(0, 0);

	///////////////////////////////////МЕНЮ///////////////////////////////////
	//0 - выход, 1 - главное меню, 2 - один игрок, 3 - сетевая  4 - настройки
	int menuNum = 1;
	sf::Event event;
	while (window.waitEvent(event))
	{
		window.clear();
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
			if (Keyboard::isKeyPressed(Keyboard::Escape)) { 
				wait(200);
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
			return 3;
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
			if (Keyboard::isKeyPressed(Keyboard::Escape)) {
				std::this_thread::sleep_for(std::chrono::milliseconds(200));  
				menuNum = 1;
			}

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
