#pragma once
#include <SFML/Graphics.hpp>
#include "Tank.h"
#include "td.h"


class GameInterface
{
public:
	GameInterface(sf::Texture &texture);
	~GameInterface();

	void update(struct Tank::stats stats, float deltaTime);
	void draw(sf::RenderWindow &window);
private:
	sf::Sprite plus[4];
	sf::Sprite gInterface;
	sf::Font font;
	sf::Text timeText, playerHealth, playerArmor, playerGold, playerMSLevel, playerASLevel, playerBSLevel;

	si seconds = 0;
	si minutes = 0;
	float time = 0;
};

