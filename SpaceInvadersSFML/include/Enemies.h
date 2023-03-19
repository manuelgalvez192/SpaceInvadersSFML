#pragma once
#include <SFML/Graphics.hpp>
#include "BulletsEnemy.h"

class Enemies
{
	public:
		Enemies(float offSetEnemies, float m_level, float height);

		void actionEnemies();
		void draw(sf::RenderWindow& myWindow);
		bool getIsMovingLeft() { return m_isMovingLeft; }
		sf::Sprite getSprite() { return m_invader; }
		bool getIsDead() { return m_isDead; }
		void setIsDead(bool state) { m_isDead = state; }
		void setShootProb(long moreShotProb) { m_enemyProbShoot += moreShotProb; }
		void setEnemySpeed(long moreEnemySpeed) { m_enemySpeed += moreEnemySpeed; }
		void resetShootProb();
		void resetEnemySpeed();
		void resetDirection() { m_isMovingLeft = false; }
		float getLevel() { return m_level; }
		void setEnemyPositionX(float offSet);
		void resetPositionY() { m_enemyPositionY = m_originalEnemyPositionY; }
		std::vector<BulletsEnemy> getFiredBullets() { return m_firedBullets; }
		std::vector<BulletsEnemy> getActiveBullets() { return m_activeBullets; }
		void updateVectorBullets(size_t j);

	private:
		long m_enemyPositionY;
		long m_originalEnemyPositionY;
		bool m_isMovingLeft;
		long m_enemyProbShoot;
		long m_enemyPositionX;
		float m_level;
		bool m_isDead;
		float m_reload;
		float m_enemySpeed;
		sf::Sprite m_invader;
		sf::Texture m_texture;
		std::vector<BulletsEnemy> m_activeBullets;
		std::vector<BulletsEnemy> m_firedBullets;
};