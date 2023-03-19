#include <iostream>
#include "Player.h"
#include "Values.h"
#include <SFML/Window.hpp>

Player::Player() :
	m_reload(SHOOT_COOLDOWN),
	m_lifes(PLAYER_LIFES),
	m_score(0)
{
	m_texture.loadFromFile("../data/images/spaceInvadersShip.png");
	m_player.setTexture(m_texture);
	m_player.setPosition(PLAYER_BASEX, PLAYER_BASEY);
	m_playerPositionX = m_player.getPosition().x;

	for (size_t i = 0; i < 10; i++)
	{
		m_activeBullets.push_back(*new Bullets(this->getPositionX() + 10));
	}

	
}

void Player::actionPlayer()
{
	if (1 == sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		m_playerPositionX = std::max<int>(m_playerPositionX - 1 * PLAYER_SPEED, 0);
	}

	if (1 == sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		m_playerPositionX = std::min<int>(m_playerPositionX + 1 * PLAYER_SPEED, SCREEN_WIDTH - 25);
	}

	m_player.setPosition(m_playerPositionX, PLAYER_BASEY);

	if (m_reload <= 0)
	{
		if (1 == sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			if (!m_activeBullets.empty())
			{
				m_reload = SHOOT_COOLDOWN;
				m_activeBullets.front().setPositionX(this->getPositionX() + 10);
				m_activeBullets.front().setPositionY();
				m_firedBullets.push_back(m_activeBullets.front());
				m_activeBullets.erase(m_activeBullets.begin());
			}
			
		}
	}
	else
	{
		m_reload--;
	}
}

void Player::updateVectorBullets(size_t j)
{
	m_firedBullets.at(j).setPositionY();
	m_activeBullets.push_back(m_firedBullets.front());
	m_firedBullets.erase(m_firedBullets.begin() + j);
}

void Player::draw(sf::RenderWindow& myWindow)
{
	myWindow.draw(m_player);

	if (!m_firedBullets.empty())
	{
		for (auto bullets = m_firedBullets.begin(); bullets != m_firedBullets.end(); bullets++)
		{
			if (bullets->getPositionY() < 0)
			{
				bullets->setPositionY();
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