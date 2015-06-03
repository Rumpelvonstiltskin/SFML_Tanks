#pragma once
#include "Tank.h"
#include <SFML/Graphics.hpp>
#include "gamedef.h"

class TankBot : public Tank
{
public:
	TankBot(sf::Texture &texture);
	~TankBot();
	void update(float deltaTime, sf::Vector2f playerPos, sf::Vector2f firstBulletPosition, bool playerLife, bool enemyHit);
	struct switchers {
		bool moveForward = false;
		bool moveBackward = false;
		bool rotateRight = false;
		bool rotateLeft = false;
		bool shoot = false;
	} switcher;
private:
	enum decisions {
		FORWARD_MOVEMENT = 1, BACKWARD_MOVEMENT, ROTATION_LEFT, ROTATION_RIGHT, SHOT
	};
	
	float time = 0;
	float decisionTime = 0;
	si decision;
	si upgrade;
private:
	void kill();
};

