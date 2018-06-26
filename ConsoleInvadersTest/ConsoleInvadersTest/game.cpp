/////////////////////////////////
//includes
#include "game.h"
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include "level.h"
#include "input.h"

////////////////////////////////
//logic variables
	int framesCounter = 0;
	float framesTimeCounter = 0;
	int fps = 0;
	int points = 0;
	int live = 1;
	int const bigLive = 1;
	int BigLive = bigLive;
	int randomizator;
	bool two_bullets = false;
	bool freeze = false;
	bool reload = false;

////////////////////////////////
//class game
Game::Game()
{
	m_isGameActive = true;
	m_clockLastFrame = 0;

	for (int i = 0; i < gameObjectsCountMax; i++)
		m_objects[i] = 0;

	m_shipFireCooldownTime = 0.0;
	m_alienAmplitudeTime = 0.0;
}

void Game::setupSystem()
{
	srand(time(0));

	m_renderSystem.initialize();
}

void Game::initialize()
{
	

	//load level
	for (int r = 0; r < levelRows; r++)
	{
		for (int c = 0; c < levelColumns; c++)
		{
			unsigned char cellSymbol = leveldata0[r][c];

			switch (cellSymbol)
			{
				//create ship
			case cellSymbol_Ship:
			{
				GameObject* heroShip= createObject(GameObjectType_Ship,
					(c + 0.5),
					r,
					GetRenderCellSymbol(cellSymbol),
					GetRenderCellSymbolColor(cellSymbol),
					GetRenderCellSymbolBackgroundColor(cellSymbol));
				break;
			}

			//create alien
			case cellSymbol_Alien:
			{
				GameObject* alien = createObject(GameObjectType_Alien,
					(c + 0.5),
					r,
					GetRenderCellSymbol(cellSymbol),
					GetRenderCellSymbolColor(cellSymbol),
					GetRenderCellSymbolBackgroundColor(cellSymbol));

				alien->setXSpeed(alienAmplitude * cos(m_alienAmplitudeTime));
				alien->setYSpeed(alienSpeed);
				break;
			}
			case cellSymbol_Alien_Big:
			{
				GameObject* alien_big = createObject(GameObjectType_Alien_Big,
					(c + 0.5),
					r,
					GetRenderCellSymbol(cellSymbol),
					GetRenderCellSymbolColor(cellSymbol),
					GetRenderCellSymbolBackgroundColor(cellSymbol));

				alien_big->setXSpeed(alienAmplitude * cos(m_alienAmplitudeTime));
				alien_big->setYSpeed(alienSpeed);
				break;
			}
			}

		}
	//set clocklastframe
	m_clockLastFrame = clock();
	m_shipFireCooldownTime = 0.0;
	m_alienAmplitudeTime = 0.0;
	}
}

bool Game::frame()
{
	//calculate delta time
	clock_t clockNow = clock();
	clock_t deltaClock = clockNow - m_clockLastFrame;
	float deltaTime = float(deltaClock) / CLOCKS_PER_SEC;
	m_clockLastFrame = clockNow;

	render();
	update(deltaTime);

	return m_isGameActive;
}

void Game::shutdown()
{
	for(int i=0;i<gameObjectsCountMax;i++)
		if (m_objects[i] != 0)
		{
			delete m_objects[i];
			m_objects[i] = 0;
		}
}

void Game::render()
{
	//start frame 
	m_renderSystem.clear();

	//draw fps
	char textBuffer[32];
	sprintf_s(textBuffer, "FPS: %d", fps);
	m_renderSystem.drawText(0, 0, textBuffer, consoleColor_Gray, consoleColor_Black);

	//draw points
	char pointBuff[16];
	sprintf_s(pointBuff, "Points: %d", points);
	m_renderSystem.drawText(0, 28, pointBuff, consoleColor_Gray, consoleColor_Black);

	//draw all game objects
	int objectsCount = 0;
	for (int i = 0; i < gameObjectsCountMax; i++)
		if (m_objects[i] != 0)
		{
			m_objects[i]->render(&m_renderSystem);
			objectsCount++;
	}

	//draw objects count
	char buff[64];
	sprintf_s(buff, "Objs: %d", objectsCount);
	m_renderSystem.drawText(0, 14, buff, consoleColor_Gray, consoleColor_Black);

	//end frame
	m_renderSystem.flush();
}

void Game::update(float dt)
{
	
	int percentChance;
	//randomize for random bonus
	percentChance = rand() % 10 + 1;
	randomizator = rand() % 3 + 1;
	//calculate deltaTime
	clock_t m_clockNow = clock();
	clock_t m_deltaClock = m_clockNow - m_clockLastFrame;
	float m_deltaTime = float(m_deltaClock) / CLOCKS_PER_SEC;
	m_clockLastFrame = m_clockNow;
	
	

	//calculate fps
	framesCounter++;
	framesTimeCounter += m_deltaTime;
	if (framesTimeCounter >= 1.0)
	{
		framesTimeCounter -= 1.0;
		fps = framesCounter;
		framesCounter = 0;
	}

	bool haveAliveAliens = false;

	//update all game objects

		for (int i = 0; i < gameObjectsCountMax; i++)
		{
			GameObject* object = m_objects[i];

			if (object != 0)
			{
				object->update(dt);

				switch (object->getType())
				{
					//hero ship
				case GameObjectType_Ship:
				{
					//borders
					if (object->getX() < 0)
						object->setX(0);
					else
						if (object->getX() > screenColumns - 1)
							object->setX(screenColumns - 1);

					//move
					if (isKeyDown(VK_LEFT))
						object->setXSpeed(-shipSpeed);
					else
						if (isKeyDown(VK_RIGHT))
							object->setXSpeed(shipSpeed);
						else
							object->setXSpeed(0.0);

					//fire
					if (isKeyDown(VK_SPACE))
					{
						if (m_shipFireCooldownTime <= 0.0 && !two_bullets)
						{
								m_shipFireCooldownTime = shipFireCooldown;

								//create bullet
								GameObject* bullet = createObject(GameObjectType_Bullet,
									object->getX(),
									object->getY() - 1,
									GetRenderCellSymbol(cellSymbol_Bullet),
									GetRenderCellSymbolColor(cellSymbol_Bullet),
									GetRenderCellSymbolBackgroundColor(cellSymbol_Bullet));
								bullet->setYSpeed(-bulletSpeed);
						}
						else if(m_shipFireCooldownTime <= 0.0 && two_bullets)
							{
								m_shipFireCooldownTime = shipFireCooldown;
								//create 2 bullets
								GameObject* bullet1 = createObject(GameObjectType_Bullet,
									object->getX() + 0.5,
									object->getY() - 1,
									GetRenderCellSymbol(cellSymbol_Bullet),
									GetRenderCellSymbolColor(cellSymbol_Bullet),
									GetRenderCellSymbolBackgroundColor(cellSymbol_Bullet));
								bullet1->setYSpeed(-bulletSpeed);
								GameObject* bullet2 = createObject(GameObjectType_Bullet,
									object->getX() - 0.5,
									object->getY() - 1,
									GetRenderCellSymbol(cellSymbol_Bullet),
									GetRenderCellSymbolColor(cellSymbol_Bullet),
									GetRenderCellSymbolBackgroundColor(cellSymbol_Bullet));
								bullet2->setYSpeed(-bulletSpeed);
							}
					}
				}

				//Bullet 
				case GameObjectType_Bullet:
				{
					if (object->getY() < 0)
					{
						destroyObject(object);
					}
					else
					{
						for (int e = 0; e < gameObjectsCountMax; e++)
						{
							GameObject* anotherObject = m_objects[e];

							if (anotherObject != 0)
							{
								if (anotherObject->getType() == GameObjectType_Alien)
								{
									if (anotherObject->intersects(object))
									{
										if (live == 1)
										{

											//destroy alien
											destroyObject(anotherObject);

											//create random bonus
										
												GameObject* bon1 = createObject(GameObjectType_Bonus_DoubleShot,
													object->getX(),
													object->getY() + 1,
													GetRenderCellSymbol(cellSymbol_Bonus_DoubleShot),
													GetRenderCellSymbolColor(cellSymbol_Bonus_DoubleShot),
													GetRenderCellSymbolBackgroundColor(cellSymbol_Bonus_DoubleShot));
												bon1->setYSpeed(bonusSpeed);

											//destroy bullet /+ points

											points += rand() % 3 + 1;
											destroyObject(object);
											break;
										}
									}
								}

								else if (anotherObject->getType() == GameObjectType_Alien_Big)
								{
									if (anotherObject->intersects(object))
									{
										if (BigLive < 1)
										{
											//destroy big alien
											destroyObject(anotherObject);

											//create random bonus

											//create new object
											GameObject* alien = createObject(GameObjectType_Alien,
												object->getX() - 0.5,
												object->getY(),
												GetRenderCellSymbol(cellSymbol_Alien_Red),
												GetRenderCellSymbolColor(cellSymbol_Alien_Red),
												GetRenderCellSymbolBackgroundColor(cellSymbol_Alien_Red));

											alien->setXSpeed(alienAmplitude*cos(m_alienAmplitudeTime));
											alien->setYSpeed(alienSpeed);
											//create second object
											GameObject* alien1 = createObject(GameObjectType_Alien,
												object->getX() + 0.5,
												object->getY(),
												GetRenderCellSymbol(cellSymbol_Alien_Red),
												GetRenderCellSymbolColor(cellSymbol_Alien_Red),
												GetRenderCellSymbolBackgroundColor(cellSymbol_Alien_Red));

											alien1->setXSpeed(alienAmplitude*cos(m_alienAmplitudeTime));
											alien1->setYSpeed(alienSpeed);


											//destroy bullet /+ points
											destroyObject(object);
											points += rand() % 5 + 3;

											BigLive = bigLive;
											break;
										}
										else
										{
											destroyObject(object);
											BigLive--;
										}
									}
								}
							}
						}
					}

					break;
				}
				
				//behavior of bonus_DoubleShot
				case GameObjectType_Bonus_DoubleShot:
				{
					if (object->getY() >= screenRows)
						destroyObject(object);
					break;
				}
				//behavior of bonus_Freeze
				case GameObjectType_Bonus_Freeze:
				{
					if (object->getY() >= screenRows)
						destroyObject(object);
					break;
				}
				//behavior of bonus_Reload
				case GameObjectType_Bonus_Reload:
				{
					if (object->getY() >= screenRows)
						destroyObject(object);
					break;
				}

				//alien ship
				case GameObjectType_Alien:
				{
					haveAliveAliens = true;
					if (!freeze)
					{
						if (object->getY() >= screenRows)
							m_isGameActive = false;
						else
							object->setXSpeed(alienAmplitude * cos(m_alienAmplitudeTime));
					}
					else
					{
						object->setXSpeed(alienAmplitudeFreeze * cos(m_alienAmplitudeTime));
						object->setYSpeed(alienSpeedFreeze);
					}

					break;
				}
				case GameObjectType_Alien_Big:
				{
					haveAliveAliens = true;
					if (!freeze)
					{
						if (object->getY() >= screenRows)
							m_isGameActive = false;
						else
							object->setXSpeed(alienAmplitude * cos(m_alienAmplitudeTime));
					}
					else
					{
						object->setXSpeed(alienAmplitudeFreeze * cos(m_alienAmplitudeTime));
						object->setYSpeed(alienSpeedFreeze);
					}

					break;
				}
				}
			}
		}
	//ship cooldown time
	if (m_shipFireCooldownTime > 0.0)
		m_shipFireCooldownTime -= dt;

	//alien amplitude time 
	m_alienAmplitudeTime += dt;

	//victory
	if (!haveAliveAliens)
		m_isGameActive = false;
}

GameObject* Game::createObject(GameObjectType type, float x, float y, char symbol, consoleColor color, consoleColor bgColor)
{
	//find free poiter and create object
	for (int i = 0; i < gameObjectsCountMax; i++)
	{
		if (m_objects[i] == 0)
		{
			GameObject* object = new GameObject();

			object->setType(type);
			object->setX(x);
			object->setY(y);
			object->setSymbol(symbol);
			object->setColor(color);
			object->setBackgroundColor(bgColor);

			m_objects[i] = object;
			return object;
		}
	}
	
	return 0;
}

void Game::destroyObject(GameObject* object)
{
	for (int i = 0; i < gameObjectsCountMax; i++)
	{
		if (m_objects[i] == object)
		{
			delete m_objects[i];
			m_objects[i] = 0;
			return;
		}
	}
}