#include "BulletsEnemy.h"
#include "Values.h"
#include <iostream>

BulletsEnemy::BulletsEnemy(long positionEnemyX, long positionEnemyY)
{
	m_bullet = sf::RectangleShape(sf::Vector2f(5, 15));
	m_bullet.setFillColor(sf::Color::White);
	m_bullet.setPosition(positionEnemyX, positionEnemyY);

	m_bulletPositionY = positionEnemyY;
	m_bulletPositionX = positionEnemyX;
}

void BulletsEnemy::setPositionY(long positionEnemyY)
{
	m_bulletPositionY = positionEnemyY;
}

void BulletsEnemy::setPositionX(long positionPlayerX)
{
	m_bulletPositionX = positionPlayerX;
}

void BulletsEnemy::draw(sf::RenderWindow& myWindow)
{
	if (m_bullet.getPosition().y <= 1080)
	{
		m_bullet.setPosition(m_bulletPositionX, m_bulletPositionY);
		m_bulletPositionY += BULLET_ENEMY_SPEED;
		myWindow.draw(m_bullet);
	}
}
