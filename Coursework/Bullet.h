#pragma once
#include <SFML/Graphics.hpp>
class Bullet
{
public:
	bool life = true;
public:
	Bullet(sf::Texture &texture, sf::Vector2f gun_pos, float angle, float level);
	~Bullet();

	void update(float deltaTime);
	void draw(sf::RenderWindow &window);
	
	sf::Vector2f getPosition();
private:
	sf::Texture bulletTexture;
	sf::Sprite bullet;

	float dx = 35;
	float dy = 35;
};

