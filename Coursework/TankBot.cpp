#include "TankBot.h"
#include "Tank.h"


TankBot::TankBot(sf::Texture &texture) : Tank(texture)
{
	tankBody.setPosition(1420, 500);
	tankGun.setPosition(1420, 500);
	drawPriority = 0;
}


void TankBot::update(float deltaTime, sf::Vector2f playerPos, sf::Vector2f firstBulletPosition, bool playerLife, bool enemyHit)
{
	this->enemyHit = enemyHit;
	if (enemyHit) {
		if (stats.armor) {
			stats.armor -= 10;
		}
		else {
			stats.healingPoints -= 10;
		}
	}
	this->enemyHit = false;

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
		if (b->hit) {
			explode(b->getPosition());
			hitDelayTime = 100;
			this->enemyHit = true;
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

	if (stats.healingPoints <= 0) {
		life = false;
		kill();
		return;
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

	if (decisionTime <= 0) {
		decisionTime = (100 + static_cast <float> (rand() % 2000)) / 10;
		decision = 3 + rand() % 2;
		time = 0;
		if (rand() % 4) {
			if (rand() % 2) {
				decision = SHOT;
				decisionTime = (300 + static_cast <float> (rand() % 3000)) / 10;
			}
			else {
				decisionTime = (1000 + static_cast <float> (rand() % 3000)) / 10;
				if (tankBodyAngle > 280 && tankBodyAngle < 80) {
					if (tankPos.y < 280) {
						decision = BACKWARD_MOVEMENT;
					}
					else if (tankPos.y > 1440) {
						decision = FORWARD_MOVEMENT;
					}
					else {
						if (rand() % 2) {
							decision = FORWARD_MOVEMENT;
						}
						else {
							decision = BACKWARD_MOVEMENT;
						}
					}
				}

				if (tankBodyAngle > 100 && tankBodyAngle < 260) {
					if (tankPos.y < 280) {
						decision = FORWARD_MOVEMENT;
					}
					else if (tankPos.y > 1440) {
						decision = BACKWARD_MOVEMENT;
					}
					else {
						if (rand() % 2) {
							decision = FORWARD_MOVEMENT;
						}
						else {
							decision = BACKWARD_MOVEMENT;
						}
					}
				}
			}
		}
		else {

		}
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
			switcher.rotateLeft = true;
			break;
		case ROTATION_RIGHT:
			switcher.rotateRight = true;
			break;
		case SHOT:
			if (angle != tankGun.getRotation()) {
				if (atan2(tankPos.x - playerPos.x, tankPos.y - playerPos.y) > 0) {
					switcher.rotateRight = true;
				}
				else {
					switcher.rotateRight = false;
				}

				if (atan2(tankPos.x - playerPos.x, tankPos.y - playerPos.y) < 0) {
					switcher.rotateLeft = true;
				}
				else {
					switcher.rotateLeft = false;
				}
			}
			else {
				switcher.rotateRight = false;
				switcher.rotateLeft = false;
			}
			break;
		default:
			break;
		}
	}
	else {
		switcher.moveForward = false;
		switcher.moveBackward = false;
		switcher.rotateLeft = false;
		switcher.rotateRight = false;
	}

	// move
	movementSpeed = 0.3 + 0.1 * stats.msLevel;
	tankBodyAngle = tankBodyAngle * 3.14 / 180;

	if (switcher.rotateLeft) {
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
}


void TankBot::kill()
{
	if (respawnTime > 0) {
		tankBody.setPosition(-300, -300);
		tankGun.setPosition(-300, -300);
		switcher.shoot = false;
		respawnTime -= deltaTime;
	}
	else {
		tankBody.setPosition(1420, 500);
		tankGun.setPosition(1420, 500);
		stats.healingPoints = 100;
		respawnTime = 3000;
	}
}


TankBot::~TankBot()
{
}