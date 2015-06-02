#include "Map.h"


Map::Map(sf::Texture &texture)
{
	map.setTexture(texture);
	map.setTextureRect(sf::IntRect(0, 1080, 1920, 840));

	for (int i = 0; i <= 2; ++i) {
		lines[i].setSize(sf::Vector2f(5, 150));
		lines[i].setFillColor(sf::Color(44, 228, 255));
		lines[i].setPosition(875 + i * 80, -150 + pow(-1, i) * i * 50);
	}
}


void Map::draw(sf::RenderWindow &window)
{
	window.draw(map);

	for (int i = 0; i <= 2; ++i)
		window.draw(lines[i]);
}


void Map::update(float deltaTime)
{
	for (int i = 0; i <= 2; ++i)
		lines[i].move(0, 0.5 * deltaTime);

	if (lines[1].getPosition().y > 1080)
		for (int i = 0; i <= 2; ++i)
			lines[i].setPosition(875 + i * 80, -150 + pow(-1, i) * i * 50);
}


Map::~Map()
{
}
