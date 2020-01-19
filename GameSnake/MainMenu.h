#pragma once

#include <iostream>
#include <Windows.h>
#include "Math.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>


//TODO ����������� � �������� ������
//TODO ������� ��� ������ ��� ������� �� ������� � ����� ��������
//TODO ������� ����������� ������� �� �����


//�������� ��������� ����� ��� ���������
bool MouseOnSprite(RenderWindow& window, Sprite sprite) {
	if (sprite.getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y)) return true;
	else return false;
}

unsigned short int MainMenu(RenderWindow& window) {
	
	//����� ��������� ����
	Vector2u windowParam = window.getSize(); 
	std::cout << windowParam.x << ' ' << windowParam.y << std::endl;
	
	//�������� ��������� ��� ���������� �������� �� ������
	Vector2f scale((float)windowParam.x/PreScaleX, (float)windowParam.y/PreScaleY); 
	std::cout << scale.x << ' ' << scale.y;

	//�������� ��� �������� ����
	Texture SoloGameTexture, MultiGameTexture, SettingsTexture, ExitTexture, MMBackgroundTexture; 
	SoloGameTexture.loadFromFile("images/SoloGameBt.png");
	MultiGameTexture.loadFromFile("images/MultiplayerBt.png");
	SettingsTexture.loadFromFile("images/SettingsBt.png");
	ExitTexture.loadFromFile("images/ExitBt.png");
	MMBackgroundTexture.loadFromFile("images/MainmenuBg.jpg");
	Sprite SoloButton(SoloGameTexture), MultiplayerButton(MultiGameTexture), ExitButton(ExitTexture), SettingsButton(SettingsTexture), MainMenuBg(MMBackgroundTexture);

	//�������� ��� ��������
	Texture SettingsBackgroundTexture; 
	SettingsBackgroundTexture.loadFromFile("images/SettingsBg.jpg");
	Sprite SettingsBg(SettingsBackgroundTexture);

	//�������� ��� ������������� � ������
	Texture YesTexture, NoTexture, SureTexture; 
	YesTexture.loadFromFile("images/YesBt.png");
	NoTexture.loadFromFile("images/NoBt.png");
	SureTexture.loadFromFile("images/SureBt.png");
	Sprite YesButton(YesTexture), NoButton(NoTexture), SureQuestion(SureTexture);

	//�������� ��� ������ �������� � ������� ����
	Texture ReturnToMainmenuTexture; 
	ReturnToMainmenuTexture.loadFromFile("images/ReturnBt.png");
	Sprite ReturnMMButton(ReturnToMainmenuTexture);

	//������ ������� 
	
	//����������� ������� ��� ����
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

	//����������� ��������� ������ � ����
	SoloButton.setPosition(trunc(windowParam.x * 0.05), trunc(windowParam.y * 0.05));
	MultiplayerButton.setPosition(trunc(windowParam.x * 0.05), trunc(windowParam.y * 0.25));
	SettingsButton.setPosition(trunc(windowParam.x * 0.05), trunc(windowParam.y * 0.45));
	ExitButton.setPosition(trunc(windowParam.x * 0.05), trunc(windowParam.y * 0.75));
	NoButton.setPosition(trunc(windowParam.x * 0.58), trunc(windowParam.y * 0.60));
	YesButton.setPosition(trunc(windowParam.x * 0.33), trunc(windowParam.y * 0.60));
	SureQuestion.setPosition(trunc(windowParam.x * 0.25), trunc(windowParam.y * 0.4));
	ReturnMMButton.setPosition(trunc(windowParam.x * 0.75), trunc(windowParam.y * 0.90));
	
	//��������� ���� �� ���������
	SettingsBg.setPosition(0, 0);
	MainMenuBg.setPosition(0, 0);
	MultiPlayerBg.setPosition(0, 0);

	
	///////////////////////////////////����///////////////////////////////////
	//0 - �����, 1 - ������� ����, 2 - ���� �����, 3 - �������  4 - ���������
	int menuNum = 1;
	sf::Event event;
	while (window.waitEvent(event))
	{
		//���� 1
		if (menuNum == 1) {
			SoloButton.setColor(Color::White);
			MultiplayerButton.setColor(Color::White);
			SettingsButton.setColor(Color::White);
			ExitButton.setColor(Color::White);

			//��������� ����� ��� ��������� ���������
			if (MouseOnSprite(window,SoloButton))
				SoloButton.setColor(Color::Green);
			else if (MouseOnSprite(window, MultiplayerButton))
				MultiplayerButton.setColor(Color::Green);
			else if (MouseOnSprite(window, SettingsButton))
				SettingsButton.setColor(Color::Green);
			else if (MouseOnSprite(window, ExitButton))
				ExitButton.setColor(Color::Red);

			//��������� ��� ������� ����
			if (Mouse::isButtonPressed(Mouse::Left) && MouseOnSprite(window, SoloButton)) //������� � ������ ����
				menuNum = 2;
			else if (Mouse::isButtonPressed(Mouse::Left) && MouseOnSprite(window, MultiplayerButton)) //������� � ���� ������� ����
				menuNum = 3;
			else if (Mouse::isButtonPressed(Mouse::Left) && MouseOnSprite(window, SettingsButton)) //������� � ���� ��������
				menuNum = 4;
			else if (Mouse::isButtonPressed(Mouse::Left) && MouseOnSprite(window, ExitButton)) //������� � ������� ������
				menuNum = 0;

			//������� �� esc
			if (Keyboard::isKeyPressed(Keyboard::Escape)) menuNum = 0;

			window.draw(MainMenuBg);
			window.draw(SoloButton);
			window.draw(MultiplayerButton);
			window.draw(ExitButton);
			window.draw(SettingsButton);
		}

		//���� 2 - ���������
		if (menuNum == 2) {
			return 2;
		}
		//���� 3 - �������
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
		//���� 4 - ���������
		if (menuNum == 4) {

			ReturnMMButton.setColor(Color::White);
			if (MouseOnSprite(window, ReturnMMButton)) {
				ReturnMMButton.setColor(Color::Red);
				if (Mouse::isButtonPressed(Mouse::Left)) //������� � ������� ����
					menuNum = 1;
			}

			//������� �� esc
			if (Keyboard::isKeyPressed(Keyboard::Escape)) menuNum = 1;

			window.draw(SettingsBg);
			window.draw(ReturnMMButton);
		}

		//������� ������
		if (menuNum == 0) {
			YesButton.setColor(Color::White);
			NoButton.setColor(Color::White);

			//��������� ����� ��� ���������
			if (MouseOnSprite(window, YesButton))
				YesButton.setColor(Color::Red);
			else if (MouseOnSprite(window, NoButton))
				NoButton.setColor(Color::Green);

			//��������� ��� �������
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
