#include "GameController.h"
#include "Values.h"
#include "Bullets.h"
#include "LevelController.h"
#include <SFML/Window.hpp>
#include <thread>
#include <iostream>

GameController::GameController() :
	m_window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Space Invaders!")
{

}

void GameController::update()
{
    sf::Clock deltaClock;
    sf::Time deltaTime = deltaClock.restart();

    sf::Text messageLevel;
    sf::Font font;
    font.loadFromFile("../data/font/arcade.ttf");
    messageLevel.setFont(font);
    messageLevel.setCharacterSize(60);
    messageLevel.setFillColor(sf::Color::White);
    messageLevel.setPosition(100, 100);

    sf::Text messageLifes;
    messageLifes.setFont(font);
    messageLifes.setCharacterSize(15);
    messageLifes.setFillColor(sf::Color::White);
    messageLifes.setPosition(20, 1040);

    sf::Text messageScore;
    messageScore.setFont(font);
    messageScore.setCharacterSize(15);
    messageScore.setFillColor(sf::Color::White);
    messageScore.setPosition(1750, 1040);

    sf::Text messageWin;
    messageWin.setFont(font);
    messageWin.setCharacterSize(80);
    messageWin.setFillColor(sf::Color::Green);
    messageWin.setPosition(650, 450);

    sf::Text messageGO;
    messageGO.setFont(font);
    messageGO.setCharacterSize(80);
    messageGO.setFillColor(sf::Color::Red);
    messageGO.setPosition(650, 450);

    m_window.setFramerateLimit(60);

    Player p1;
    LevelController lc;

    std::vector<Enemies> activeEnemy;
    std::vector<Enemies> deadEnemy;

    float offsetEnemies = 0;

    activeEnemy = lc.createLevel(activeEnemy, offsetEnemies);
    bool firstLevel = true;
    bool crash;
    while (m_window.isOpen())
    {
        p1.actionPlayer();

        m_window.clear();
        p1.draw(m_window);

        for (size_t i = 0; i < activeEnemy.size(); i++)
        {
            activeEnemy.at(i).actionEnemies();
        }

        for (size_t i = 0; i < activeEnemy.size(); i++)
        {
            activeEnemy[i].draw(m_window);
        }

        deltaTime = deltaClock.restart();
        crash = isInvaderCrashing(activeEnemy, p1);
        if (p1.getLifes() == 0 || crash)
        {
            messageGO.setString("GAME OVER");
            messageScore.setCharacterSize(30);
            messageScore.setPosition(650,550);
            sf::Time timeElapsed;
            while ((timeElapsed = deltaClock.getElapsedTime()).asMilliseconds() < 2000)
            {
                m_window.clear();
                m_window.draw(messageGO);
                m_window.draw(messageScore);
                m_window.display();
            }

            activeEnemy.clear();
            deadEnemy.clear();

            lc.resetHeight();
            lc.resetLevel();
            p1.resetScore();
            p1.setLifes(3);
            offsetEnemies = 0;
            activeEnemy = lc.createLevel(activeEnemy, offsetEnemies);
            crash = false;

            firstLevel = true;
            lc.resetLevel();
        }

        if (firstLevel)
        {
            messageLevel.setString("Level " + std::to_string(static_cast<int>(lc.getLevel())));

            sf::Time timeElapsed;
            while ((timeElapsed = deltaClock.getElapsedTime()).asMilliseconds() < 2000)
            {
                m_window.clear();
                m_window.draw(messageLevel);
                m_window.display();
            }
            firstLevel = false;
        }
        if (lc.getLevel() == 3 && activeEnemy.empty())
        {
            messageWin.setString("YOU WIN");
            messageScore.setCharacterSize(30);
            messageScore.setPosition(650, 550);
            sf::Time timeElapsed;
            while ((timeElapsed = deltaClock.getElapsedTime()).asMilliseconds() < 2000)
            {
                m_window.clear();
                m_window.draw(messageWin);
                m_window.draw(messageScore);
                m_window.display();
            }

            activeEnemy.clear();
            deadEnemy.clear();

            lc.resetHeight();
            lc.resetLevel();
            p1.resetScore();
            p1.setLifes(3);
            offsetEnemies = 0;
            activeEnemy = lc.createLevel(activeEnemy, offsetEnemies);

            firstLevel = true;
            lc.resetLevel();
        }
        else
            if (activeEnemy.empty())
            {
                offsetEnemies = 0;

                for (size_t z = 0; z < deadEnemy.size(); z++)
                {
                    if (z % 20 == 0)
                    {
                        offsetEnemies = 0;
                    }

                    activeEnemy.push_back(deadEnemy.at(z));
                    activeEnemy.at(z).setEnemyPositionX(offsetEnemies);
                    activeEnemy.at(z).resetDirection();
                    activeEnemy.at(z).resetPositionY();
                    activeEnemy.at(z).resetEnemySpeed();
                    activeEnemy.at(z).resetShootProb();
                    offsetEnemies += 55;
                }

                for (size_t z = 0; z < deadEnemy.size(); z++)
                {
                    deadEnemy.erase(deadEnemy.begin() + z);
                    break;
                }

                lc.levelUp();
                offsetEnemies = 0;
                activeEnemy = lc.createLevel(activeEnemy, offsetEnemies);

                messageLevel.setString("Level " + std::to_string(static_cast<int>(lc.getLevel())));

                sf::Time timeElapsed;
                while ((timeElapsed = deltaClock.getElapsedTime()).asMilliseconds() < 2000)
                {
                    m_window.clear();
                    m_window.draw(messageLevel);
                    m_window.display();
                }
            }


        sf::Event event;

        while (m_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                m_window.close();
        }

        for (size_t i = 0; i < activeEnemy.size(); i++)
        {
            for (size_t j = 0; j < p1.getFiredBullets().size(); j++)
            {
                if (p1.getFiredBullets()[j].getSprite().getGlobalBounds().intersects(activeEnemy[i].getSprite().getGlobalBounds()))
                {
                    deadEnemy.push_back(activeEnemy.at(i));
                    activeEnemy.erase(activeEnemy.begin() + i);
                    p1.updateVectorBullets(j);
                    p1.setScore(10);
                    break;
                }
            }
        }

        for (size_t i = 0; i < activeEnemy.size(); i++)
        {
            for (size_t j = 0; j < activeEnemy.at(i).getFiredBullets().size(); j++)
            {
                if (activeEnemy.at(i).getFiredBullets()[j].getSprite().getGlobalBounds().intersects(p1.getSprite().getGlobalBounds()))
                {
                    p1.substractLifes();
                    activeEnemy.at(i).updateVectorBullets(j);
                }
            }
        }

        messageLifes.setString("Lifes: " + std::to_string(static_cast<int>(p1.getLifes())));
        m_window.draw(messageLifes);


        messageScore.setCharacterSize(15);
        messageScore.setPosition(1750, 1040);
        messageScore.setString("Score: " + std::to_string(static_cast<int>(p1.getScore())));
        m_window.draw(messageScore);

        m_window.display();


    }

}

bool GameController::isInvaderCrashing(std::vector<Enemies> activeEnemy, Player p1)
{
    for (size_t i = 0; i < activeEnemy.size(); i++)
    {
       
        if (activeEnemy.at(i).getSprite().getGlobalBounds().intersects(p1.getSprite().getGlobalBounds()))
        {
            return true;
        }
        
    }

    return false;
}