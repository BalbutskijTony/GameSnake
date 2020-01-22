#pragma once

#include <vector>
#include <chrono>
#include <future> 
#include <thread>

#include <iostream>
#include <Windows.h>
#include <Time.h>
#include "Math.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>


#define PreScaleX 1280
#define PreScaleY 720

using namespace sf;

class Utility {

public:
	static Texture LoadingTexture;
	static Sprite LoadingSprite;
	static Vector2f scale;
	static Vector2u windowParam;
	static void set(RenderWindow& window);
	static std::chrono::milliseconds flick;

private:
	static int LoadingAngle;

};

std::chrono::milliseconds Utility::flick;
Texture Utility::LoadingTexture;
Sprite Utility::LoadingSprite;
Vector2u Utility::windowParam;
Vector2f Utility::scale;

void Utility::set(RenderWindow& window) {

	//Берем настройки окна
	Utility::windowParam = window.getSize();

	//Получаем параметры для растяжения картинок на экране
	Utility::scale.x = ((float)Utility::windowParam.x / PreScaleX);
	Utility::scale.y = ((float)Utility::windowParam.y / PreScaleY);

	//Настройка для спрайта загрузки
	LoadingTexture.loadFromFile("images/loading.png");
	Sprite Spritetmp(LoadingTexture);
	LoadingSprite = Spritetmp;

	LoadingSprite.setOrigin(sf::Vector2f(300,300));
	LoadingSprite.setScale(scale.x * 0.2, scale.y * 0.2);
	LoadingSprite.setRotation(0);

}



//Проверка положения мышки над спарайтом
bool MouseOnSprite(RenderWindow& window, Sprite sprite) {
	if (sprite.getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y)) return true;
	else return false;
}
bool MouseOnSprite(RenderWindow& window, Text text) {
	if (text.getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y)) return true;
	else return false;
}

//Вызов паузы в окне
void PauseMenu(RenderWindow& window, bool paused) {

	
	Texture PauseBgTexture, PauseTitleTexture;
	PauseBgTexture.loadFromFile("images/SnakeTexture.jpg");
	if (paused) PauseTitleTexture.loadFromFile("images/Paused.png");
	else PauseTitleTexture.loadFromFile("images/NotPaused.png");
	Sprite PauseBg(PauseBgTexture), PauseTitle(PauseTitleTexture);

	PauseBg.setScale(Utility::scale.x, Utility::scale.y);
	PauseTitle.setScale(Utility::scale.x, Utility::scale.y);

	PauseBg.setPosition(Utility::windowParam.x * 0.25, Utility::windowParam.y * 0.25);
	PauseTitle.setPosition(Utility::windowParam.x * 0.34, Utility::windowParam.y * 0.25);

	while (!Keyboard::isKeyPressed(Keyboard::Escape)) {
		window.draw(PauseBg);
		window.draw(PauseTitle);
		window.display();
	}

	std::this_thread::sleep_for(std::chrono::milliseconds(200));
}

//Вызов полосы загрузки по положению
void LoadingAnimation(RenderWindow& window, float posX, float posY, float angle) {
	Utility::LoadingSprite.setPosition(posX, posY);
	Utility::LoadingSprite.rotate(angle);
	window.draw(Utility::LoadingSprite);
	window.display();
}

//Ожидание в милисекундах
void wait(int millis) {
	std::this_thread::sleep_for(std::chrono::milliseconds(millis));
}




