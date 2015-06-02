#pragma once
#include <SFML/Graphics.hpp>
class Bullet
{
public:
	bool life = true;
public:
	Bullet(sf::Texture &texture, sf::Vector2f gunPos, float angle, float level, sf::Vector2f tankEnemyPos);
	~Bullet();

	void update(float deltaTime);
	void draw(sf::RenderWindow &window);
	
	sf::Vector2f getPosition();
private:
	sf::Texture bulletTexture;
	sf::Sprite muzzleFlash;
	sf::Sprite bullet;
	sf::Vector2f tankEnemyPos;
	sf::Vector2f gunPos;

	float delayTime = 50;
	float dx = 35;
	float dy = 35;
	float angle = 0;
	bool hit = false;
};

