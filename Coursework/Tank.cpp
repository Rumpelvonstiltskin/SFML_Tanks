#include "Tank.h"
#include <iostream>
#define ELLIPSE_Y 260 * sqrt(1 - pow(tankPos.x - 960, 2) / 3450306) - 50
#define BATTLE_ZONE (mousePos.y < 840) && (pow(mousePos.x - 960, 2) / 3450306 + pow(mousePos.y + 120, 2) / 67600 >= 1)


Tank::Tank(sf::Texture &texture)
{
	short int r, g, b;

	r = 20 + static_cast<int> (rand() % 100);
	g = 20 + static_cast<int> (rand() % 100);
	b = 20 + static_cast<int> (rand() % 100);

	tankBody.setTexture(texture);
	tankBody.setTextureRect(sf::IntRect(0, 1925, 145, 205));
	tankBody.setColor(sf::Color(r, g, b));
	tankBody.setOrigin(72.5, 137.65);
	tankBody.setPosition(500, 500);

	tankGun.setTexture(texture);
	tankGun.setTextureRect(sf::IntRect(145, 1925, 145, 205));
	tankGun.setColor(sf::Color(r, g, b));
	tankGun.setOrigin(72.5, 134.5);
	tankGun.setPosition(500, 500);

	bulletTexture = texture;
	buffer.loadFromFile("Resources\\shot.ogg");
	shot.setBuffer(buffer);
}


void Tank::draw(sf::RenderWindow &window)
{
	window.draw(tankBody);
	window.draw(tankGun);

	for (it = bullets.begin(); it != bullets.end(); it++){
		(*it)->draw(window);
	}
}


void Tank::update(float deltaTime, sf::Vector2f botPos)
{
	sf::Vector2f tankPos = tankBody.getPosition();
	sf::Vector2i mousePos = mouse.getPosition();
	float tankBodyAngle = tankBody.getRotation();

	// shot
	bulletDelayTime += deltaTime;
	shotSoundDelayTime += deltaTime;

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		if (bulletDelayTime >= 1000 - 100 * stats.asLevel) {
			if (BATTLE_ZONE) {
				bullets.push_back(new Bullet(bulletTexture, tankGun.getPosition(), tankGun.getRotation(), stats.bsLevel));
				if (shotSoundDelayTime > 100) {
					shot.play();
					shotSoundDelayTime = 0;
				}
			}
			bulletDelayTime = 0;
		}
	}

	for (it = bullets.begin(); it != bullets.end();) {
		Bullet *b = *it;
		if (b->life == false) {
			it = bullets.erase(it);
			delete b;
		}
		else it++;
	}

	for (it = bullets.begin(); it != bullets.end(); it++) {
		(*it)->update(deltaTime, botPos);
	}

	// gun rotation
	sf::Vector2f gunPos = tankGun.getPosition();

	float dx = mouse.getPosition().x - gunPos.x;
	float dy = mouse.getPosition().y - gunPos.y;

	float angle = atan2(dy, dx) * 180 / 3.14 + 90;

	if (dy < 0 && dx < 0) {		// have no idea why
		angle += 360;
	}

	if (abs(tankBodyAngle - angle) < 30 || abs(tankBodyAngle - angle) > 330) {
		tankGun.setRotation(angle);
	}

	// upgrade
	secondCounterOne += deltaTime;
	secondCounterTwo += deltaTime;

	if (secondCounterOne >= 1000) {
		stats.gold++;
		secondCounterOne = 0;
	}

	if (tankPos.x > 70 && tankPos.x < 100 && tankPos.y > 525 && tankPos.y < 555) {
		stats.upgradeAvailability = true;
	}
	else {
		stats.upgradeAvailability = false;
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && stats.upgradeAvailability == true) {
		if (secondCounterTwo > 300) {
			if (mousePos.y > 1035 && mousePos.y < 1075 && stats.gold >= 100) {
				if (mousePos.x > 430 && mousePos.x < 470) {
						stats.gold -= 100;
						stats.msLevel += 1;
						secondCounterTwo = 0;
				}

				if (mousePos.x > 730 && mousePos.x < 770) {
					stats.gold -= 100;
					stats.asLevel += 1;
					secondCounterTwo = 0;
				}

				if (mousePos.x > 1030 && mousePos.x < 1070) {
					stats.gold -= 100;
					stats.bsLevel += 1;
					secondCounterTwo = 0;
				}

				if (mousePos.x > 1330 && mousePos.x < 1370) {
					stats.gold -= 100;
					stats.armor += 100;
					secondCounterTwo = 0;
				}
			}
		}
	}
	//std::cout << mouse.getPosition().x << "    " << mouse.getPosition().y << std::endl; // DELETE THIS

	// move
	movementSpeed = 0.3 + stats.msLevel * 0.1;
	tankBodyAngle = tankBodyAngle * 3.14 / 180;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		tankBody.rotate(-rotationSpeed * deltaTime);
		tankGun.rotate(-rotationSpeed * deltaTime);
		return;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		tankBody.rotate(rotationSpeed * deltaTime);
		tankGun.rotate(rotationSpeed * deltaTime);
		return;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		tankBody.move(movementSpeed * sin(tankBodyAngle) * deltaTime, -movementSpeed * cos(tankBodyAngle) * deltaTime);
		tankGun.move(movementSpeed * sin(tankBodyAngle) * deltaTime, -movementSpeed * cos(tankBodyAngle) * deltaTime);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		tankBody.move(-movementSpeed * sin(tankBodyAngle) * deltaTime, movementSpeed * cos(tankBodyAngle) * deltaTime);
		tankGun.move(-movementSpeed * sin(tankBodyAngle) * deltaTime, movementSpeed * cos(tankBodyAngle) * deltaTime);
	}

	// collision
	if (tankPos.x > 762.5) {
		tankBody.setPosition(762.5, tankPos.y);
		tankGun.setPosition(762.5, tankPos.y);
	}

	if (tankPos.x < 75) {
		tankBody.setPosition(75, tankPos.y);
		tankGun.setPosition(75, tankPos.y);
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


sf::Vector2f Tank::getTankPosition()
{
	sf::Vector2f pos = tankBody.getPosition();
	return pos;
}


float Tank::getGunRotation()
{
	return tankGun.getRotation();
}


sf::Vector2f Tank::getFirstBulletPosition()
{
	sf::Vector2f pos = { 0, 0 };
	if (bullets.size() > 0) {
		return bullets.front()->getPosition();
	}
	else {
		return pos;
	}
}


Tank::~Tank()
{
}
