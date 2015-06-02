#include "TankBot.h"
#include "Tank.h"
#define ELLIPSE_Y 260 * sqrt(1 -  pow(tankBody.getPosition().x - 960, 2) / 3450306) - 50


TankBot::TankBot(sf::Texture &texture) : Tank(texture)
{
	tankBody.setPosition(1420, 500);
	tankGun.setPosition(1420, 500);
	drawPriority = 0;
}


void TankBot::update(float deltaTime, sf::Vector2f playerPos, sf::Vector2f firstBulletPosition, bool playerLife)
{
	this->deltaTime = deltaTime;
	sf::Vector2f tankPos = tankBody.getPosition();
	float tankBodyAngle = tankBody.getRotation();

	bulletDelayTime += deltaTime;
	shotSoundDelayTime += deltaTime;

	if (switcher.shoot) {
		if (bulletDelayTime >= 1000 - 100 * stats.asLevel) {
			bullets.push_back(new Bullet(bulletTexture, tankPos, tankGun.getRotation(), stats.bsLevel));
			bulletDelayTime = 0;

			if (shotSoundDelayTime > 100) {
				shot.play();
				shotSoundDelayTime = 0;
			}
		}
	}

	for (it = bullets.begin(); it != bullets.end();) {
		Bullet *b = *it;
		if (b->hit == true) {
			explode(b->getPosition());
			hitDelayTime = 100;
		}
		if (b->life == false) {
			it = bullets.erase(it);
			delete b;
		}
		else it++;
	}

	for (it = bullets.begin(); it != bullets.end(); it++) {
		(*it)->update(deltaTime, playerPos);
	}

	//bot decisions
	float angle = atan2(tankPos.y - playerPos.y, tankPos.x - playerPos.x) * 180 / 3.14 + 270;

	if (abs(tankBodyAngle - angle) < 30 || abs(tankBodyAngle - angle) > 330) {
		tankGun.setRotation(angle);
		if (playerLife)
		switcher.shoot = true;
	}
	else {
		switcher.shoot = false;
	}

	// upgrade x = 1840, y = 540
		if (decisionTime <= 0) {
			decisionTime = (1.0 + static_cast <float> (rand() % 5000)) / 10.0;
			time = 0;
			decision = 1 + static_cast <int> (rand()) / (static_cast <int> (RAND_MAX / (5 - 1)));
		}

		decisionTime -= deltaTime;

	if (decisionTime > 0) {
		switch (decision) {
		case FORWARD_MOVEMENT:
			switcher.moveForward = true;
			break;
		case BACKWARD_MOVEMENT:
			switcher.moveBackward = true;
			break;
		case ROTATION_LEFT:
			switcher.rotationLeft = true;
			break;
		case ROTATION_RIGHT:
			switcher.rotateRight = true;
			break;
		case SHOT:
			break;
		default:
			break;
		}
	}
	else {
		switcher.moveForward = false;
		switcher.moveBackward = false;
		switcher.rotationLeft = false;
		switcher.rotateRight = false;
	}

	// collision
	if (tankPos.x < 762.5 + 145 + 270) {
		tankBody.setPosition(762.5 + 145 + 270, tankPos.y);
		tankGun.setPosition(762.5 + 145 + 270, tankPos.y);
	}

	if (tankPos.x > 1845) {
		tankBody.setPosition(1845, tankPos.y);
		tankGun.setPosition(1845, tankPos.y);
	}

	if (tankPos.y < ELLIPSE_Y) {
		tankBody.setPosition(tankPos.x, ELLIPSE_Y + 0.1);
		tankGun.setPosition(tankPos.x, ELLIPSE_Y + 0.1);
	}

	if (tankPos.y > 767.5) {
		tankBody.setPosition(tankPos.x, 767.5);
		tankGun.setPosition(tankPos.x, 767.5);
	}

	movementSpeed = 0.3 + stats.msLevel * 0.1;
	tankBodyAngle = tankBodyAngle * 3.14 / 180;

	if (switcher.rotationLeft) {
		tankBody.rotate(-rotationSpeed * deltaTime);
		tankGun.rotate(-rotationSpeed * deltaTime);
		return;
	}
		
	if (switcher.rotateRight) {
		tankBody.rotate(rotationSpeed * deltaTime);
		tankGun.rotate(rotationSpeed * deltaTime);
		return;
	}

	if (switcher.moveForward) {
		tankBody.move(movementSpeed * sin(tankBodyAngle) * deltaTime, -movementSpeed * cos(tankBodyAngle) * deltaTime);
		tankGun.move(movementSpeed * sin(tankBodyAngle) * deltaTime, -movementSpeed * cos(tankBodyAngle) * deltaTime);
	}

	if (switcher.moveBackward) {
		tankBody.move(-movementSpeed * sin(tankBodyAngle) * deltaTime, movementSpeed * cos(tankBodyAngle) * deltaTime);
		tankGun.move(-movementSpeed * sin(tankBodyAngle) * deltaTime, movementSpeed * cos(tankBodyAngle) * deltaTime);
	}
}


TankBot::~TankBot()
{
}