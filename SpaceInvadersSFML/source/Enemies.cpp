#include "Enemies.h"
#include <iostream>
#include "Values.h"

Enemies::Enemies(float offSetEnemies, float m_level, float height) :
	m_enemyProbShoot(ENEMY_SHOOT_PROB),
	m_enemyPositionX(ENEMY_BASEX + offSetEnemies),
	m_isDead(false),
	m_level(m_level),
	m_isMovingLeft(false),
	m_enemyPositionY(height),
	m_originalEnemyPositionY(height),
	m_reload(SHOOT_ENEMY_COOLDOWN),
	m_enemySpeed(ENEMY_SPEED)
{
	m_texture.loadFromFile("../data/images/invader.png");
	m_invader.setTexture(m_texture);
	m_invader.setPosition(m_enemyPositionX, m_enemyPositionY);

	for (size_t i = 0; i < 1; i++)
	{
		m_activeBullets.push_back(*new BulletsEnemy(m_enemyPositionX, m_enemyPositionY  + 25));
	}
}

void Enemies::setEnemyPositionX(float offSet)
{
	m_enemyPositionX = ENEMY_BASEX + offSet;
}

void Enemies::updateVectorBullets(size_t j)
{
	m_firedBullets.at(j).setPositionY(m_enemyPositionX);
	m_activeBullets.push_back(m_firedBullets.front());
	m_firedBullets.erase(m_firedBullets.begin() + j);
}

void Enemies::actionEnemies()
{
	if (!m_isMovingLeft)
	{
		m_enemyPositionX += (1 * m_enemySpeed);
		
		if (m_enemyPositionX >= SCREEN_WIDTH - 35)
		{
			m_enemyPositionY += 45;
			m_isMovingLeft = true;
			m_invader.setPosition(m_enemyPositionX, m_enemyPositionY);
		}
	}

	if (m_isMovingLeft)
	{
		m_enemyPositionX -= (1 * m_enemySpeed);
		
		if (m_enemyPositionX < 0)
		{
			m_enemyPositionY += 45;
			m_isMovingLeft = false;
			m_invader.setPosition(m_enemyPositionX, m_enemyPositionY);
			this->setShootProb(1);
			this->setEnemySpeed(1);
		}
	}

	if (m_reload <= 0)
	{
		int num_aleatorio = std::rand() % 700 + 1;
		if (num_aleatorio <= m_enemyProbShoot)
		{
			if (!m_activeBullets.empty())
			{
				m_reload = SHOOT_ENEMY_COOLDOWN;
				m_activeBullets.front().setPositionX(m_enemyPositionX);
				m_activeBullets.front().setPositionY(m_enemyPositionY + 25);
				m_firedBullets.push_back(m_activeBullets.front());
				m_activeBullets.erase(m_activeBullets.begin());
			}

		}
	}
	else
	{
		m_reload--;
	}
	

	m_invader.setPosition(m_enemyPositionX, m_enemyPositionY);

}

void Enemies::resetEnemySpeed()
{
	m_enemySpeed = ENEMY_SPEED;
}

void Enemies::resetShootProb()
{
	m_enemyProbShoot = ENEMY_SHOOT_PROB;
}

void Enemies::draw(sf::RenderWindow& myWindow)
{
	myWindow.draw(m_invader);

	if (!m_firedBullets.empty())
	{
		for (auto bullets = m_firedBullets.begin(); bullets != m_firedBullets.end(); bullets++)
		{
			if (bullets->getPositionY() > 1080)
			{
				bullets->setPositionY(m_enemyPositionY);
				m_activeBullets.push_back(m_firedBullets.front());
				m_firedBullets.erase(bullets);
				break;
			}
			else
			{
				bullets->draw(myWindow);
			}
		}
	}
}