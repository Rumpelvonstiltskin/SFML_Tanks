#pragma once
#include <SFML/Graphics.hpp>
class Bullet
{
public:
	bool life = true;
	bool hit = false;
public:
	Bullet(sf::Texture &texture, sf::Vector2f gunPos, float angle, float level);
	~Bullet();

	void update(float deltaTime, sf::Vector2f tankEnemyPos);
	void draw(sf::RenderWindow &window);
	
	sf::Vector2f getPosition();
private:
	sf::Texture bulletTexture;
	sf::Sprite muzzleFlash;
	sf::Sprite bullet;
	sf::Vector2f gunPos;

	float delayTime = 25;
	float dx = 35;
	float dy = 35;
	float angle = 0;
};

