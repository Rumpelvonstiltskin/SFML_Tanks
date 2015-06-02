#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Bullet.h"
#pragma once
class Tank
{
public:
	Tank(sf::Texture &texture);
	~Tank();
	sf::Vector2f getTankPosition();
	sf::Vector2f getFirstBulletPosition();

	virtual void update(float deltaTime, sf::Vector2f botPos, bool enemyHit);
	void draw(sf::RenderWindow &window);
	float getGunRotation();
public:
	struct stats {
		int healing_points = 100;
		int armor = 0;
		int gold = 7000;
		int msLevel = 1;
		int asLevel = 1;
		int bsLevel = 1;
		bool upgradeAvailability = false;
	} stats;

	bool life = true;
	int drawPriority = 1;
	bool enemyHit;
protected:
	std::vector<Bullet*> bullets;
	std::vector<Bullet*>::iterator it;

	sf::Sprite tankBody;
	sf::Sprite tankGun;
	sf::SoundBuffer buffer;
	sf::Sound shot;
	sf::Mouse mouse;
	sf::Texture bulletTexture;
	sf::Sprite explosion;

	float rotationSpeed = 0.2;
	float movementSpeed = 0.1;

	float bulletDelayTime = 0;
	float shotSoundDelayTime = 0;
	float deltaTime;
	float hitDelayTime = 100;

	float secondCounterOne = 0;
	float secondCounterTwo = 0;

	bool rotate = false;
protected:
	void explode(sf::Vector2f hitPos);
};
