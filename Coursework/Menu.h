#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "td.h"


class Menu
{
public:
	Menu();
	~Menu();

	void update(float deltaTime, si gameState);
	void draw(sf::RenderWindow &window);
	si GetPressedItem();
private:
	sf::Font about;
	sf::Font menuItems;
	sf::Text item[6];
	sf::Text aboutItem[3];
	sf::RectangleShape bar[10][2];
	sf::SoundBuffer menuThemeBuffer;
	sf::Sound menuTheme;

	si selectedItemIndexMenu = 0;
	si selectedItemIndexOptions = 4;
	si musicVolumeState = 6;
	si sfxVolumeState = 6;
	si gameState = 1;	// MENU

	float delayTime = 0;
};

