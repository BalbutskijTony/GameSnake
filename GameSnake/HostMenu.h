#pragma once

#include "UtilityFunctions.h"

bool HostMenu(RenderWindow& window) {

	//Текстуры для кнопки возврата в главное меню
	Texture ReturnToMainmenuTexture;
	ReturnToMainmenuTexture.loadFromFile("images/ReturnBt.png");
	Sprite ReturnMMButton(ReturnToMainmenuTexture);
	ReturnMMButton.setScale(Utility::scale.x * 0.5, Utility::scale.y * 0.5);

	ReturnMMButton.setPosition(trunc(Utility::windowParam.x * 0.75), trunc(Utility::windowParam.y * 0.90));
	return 0;
}