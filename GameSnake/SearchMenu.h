#pragma once

#include "UtilityFunctions.h"

bool SearchMenu(RenderWindow& window) {

	//Текстуры для меню мультиплеера
	Texture MPBackgroundTexture, MPHostSearchTexture;
	MPHostSearchTexture.loadFromFile("images/PlayerWaiting.png");
	MPBackgroundTexture.loadFromFile("images/MultiplayerBg.jpg");
	Sprite MultiPlayerBg(MPBackgroundTexture), HostSearchButton(MPHostSearchTexture);

	//Текстуры для кнопки возврата в главное меню
	Texture ReturnToMainmenuTexture;
	ReturnToMainmenuTexture.loadFromFile("images/ReturnBt.png");
	Sprite ReturnMMButton(ReturnToMainmenuTexture);

	MultiPlayerBg.setPosition(0, 0);
	MultiPlayerBg.setScale(Utility::scale.x, Utility::scale.y);

	HostSearchButton.setPosition(trunc(Utility::windowParam.x * 0.05), trunc(Utility::windowParam.y * 0.25));
	HostSearchButton.setScale(Utility::scale.x, Utility::scale.y);

	ReturnMMButton.setPosition(trunc(Utility::windowParam.x * 0.75), trunc(Utility::windowParam.y * 0.90));
	ReturnMMButton.setScale(Utility::scale.x * 0.5, Utility::scale.y * 0.5);

	vector<sf::Text> hosts;
	sf::Font font;
	font.loadFromFile("fonts/Jungle Land.ttf");
	Text text1, text2, text3;
	text1.setString("txt1");
	text2.setString("txt2");
	text3.setString("txt3");
	hosts.push_back(text1);
	hosts.push_back(text2);
	hosts.push_back(text3);

	for (int i = 0; i < 3; i++) {
		hosts[i].setCharacterSize(36);
		hosts[i].setStyle(sf::Text::Bold);
		hosts[i].setFont(font);
		hosts[i].setPosition(trunc(Utility::windowParam.x * 0.65), trunc(Utility::windowParam.y * (0.10*i+0.1)));
	}

	int menuNum = 1;
	while (menuNum) {
		for (int i = 0; i < 3; i++) 
			if (!MouseOnSprite(window, hosts[i]))
				hosts[i].setFillColor(Color::Red);
			else 
				hosts[i].setFillColor(Color::Blue);

		ReturnMMButton.setColor(Color::White);

		//Изменение цвета при наведении указателя
		if (MouseOnSprite(window, ReturnMMButton))
			ReturnMMButton.setColor(Color::Red);

		//Поведение при нажании мыши
		if (Mouse::isButtonPressed(Mouse::Left) && MouseOnSprite(window, ReturnMMButton)) //Переход к диалогу выхода
			return 0;

		//Нажатие на esc
		if (Keyboard::isKeyPressed(Keyboard::Escape)) { std::this_thread::sleep_for(std::chrono::milliseconds(200));  return 0; }
		
		window.draw(MultiPlayerBg);
		for (int i = 0; i < 3; i++)
			window.draw(hosts[i]);
		window.draw(HostSearchButton);
		window.draw(ReturnMMButton);

		LoadingAnimation(window, Utility::windowParam.x * 0.45, trunc(Utility::windowParam.y * 0.35),0.1f);
	}
	
	
}