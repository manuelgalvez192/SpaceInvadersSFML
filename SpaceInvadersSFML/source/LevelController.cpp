#include <SFML/Window.hpp>
#include <iostream>
#include "LevelController.h"

LevelController::LevelController() :
    m_level(1),
    m_height(45)
{

}


std::vector<Enemies> LevelController::createLevel(std::vector<Enemies> activeEnemy, long offsetEnemies)
{
    
    for (size_t i = 2; i <= m_level; i++)
    {
        m_height += 90;
    }
   
    for (size_t i = 0; i < 20; i++)
    {
        activeEnemy.push_back(*new Enemies(offsetEnemies, m_level, m_height));
        offsetEnemies += 55;
    }

    return activeEnemy;
}

void LevelController::resetLevel()
{
    m_level = 1;
}