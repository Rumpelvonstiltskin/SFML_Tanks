#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Menu
{
public:
	Menu();
	~Menu();

	void update(float deltaTime, int gameState);
	void draw(sf::RenderWindow &window);
	int GetPressedItem();
private:
	sf::Font about;
	sf::Font menuItems;
	sf::Text item[6];
	sf::Text aboutItem[3];
	sf::RectangleShape bar[10][2];
	sf::SoundBuffer menuThemeBuffer;
	sf::Sound menuTheme;

	int selectedItemIndexMenu = 0;
	int selectedItemIndexOptions = 4;
	int musicVolumeState = 6;
	int sfxVolumeState = 6;
	int gameState = 1;	// MENU

	float delayTime = 0;
};

