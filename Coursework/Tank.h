#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Bullet.h"
#include "gamedef.h"


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
		si healingPoints = 100;
		si armor = 0;
		si gold = 500;
		si msLevel = 1;
		si asLevel = 1;
		si bsLevel = 1;
		bool upgradeAvailability = false;
	} stats;

	bool life = true;
	si drawPriority = 1;
	bool enemyHit;
protected:
	std::vector<Bullet*> bullets;
	std::vector<Bullet*>::iterator it;

	sf::Sprite tankBody;
	sf::Sprite tankGun;
	sf::SoundBuffer shotBuf;
	sf::Sound shot;
	sf::Mouse mouse;
	sf::Texture bulletTexture;
	sf::Sprite explosion;
	sf::SoundBuffer upgradeBuf;
	sf::Sound sUpgrade;

	float rotationSpeed = 0.2;
	float movementSpeed = 0.1;

	float bulletDelayTime = 0;
	float shotSoundDelayTime = 0;
	float deltaTime;
	float hitDelayTime = 100;
	float respawnTime = 3000;

	float secondCounterOne = 0;
	float secondCounterTwo = 0;

	bool rotate = false;
protected:
	void explode(sf::Vector2f hitPos);
	virtual void kill();
};
