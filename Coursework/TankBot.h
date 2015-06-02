#pragma once
#include "Tank.h"
#include <SFML/Graphics.hpp>

class TankBot : public Tank
{
public:
	TankBot(sf::Texture &texture);
	~TankBot();
	void update(float deltaTime, sf::Vector2f playerPos, sf::Vector2f firstBulletPosition, bool playerLife);
	struct switchers {
		bool moveForward = false;
		bool moveBackward = false;
		bool rotateRight = false;
		bool rotationLeft = false;
		bool shoot = false;
	} switcher;
private:
	enum decisions {
		FORWARD_MOVEMENT = 1, BACKWARD_MOVEMENT, ROTATION_LEFT, ROTATION_RIGHT, SHOT
	};

	float time = 0;
	float decisionTime = 0;
	int decision;
};

