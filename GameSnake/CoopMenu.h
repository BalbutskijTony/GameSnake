#pragma once

#include "MainMenu.h"

unsigned short int CoopMenu(RenderWindow& window) {
	
	//Текстуры для меню мультиплеера
	Texture MPBackgroundTexture, MPHostTexture, MPSearchTexture;
	MPBackgroundTexture.loadFromFile("images/SearchBt.jpg");
	MPHostTexture.loadFromFile("images/CreateServerBt.jpg");
	MPSearchTexture.loadFromFile("images/MultiplayerBg.jpg");
	Sprite MultiPlayerBg(MPBackgroundTexture), CreateServerButton(MPHostTexture), SearchButton(MPSearchTexture);

	
}