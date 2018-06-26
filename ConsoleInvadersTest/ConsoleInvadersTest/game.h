#pragma once


////////////////////////////////
//includes
#include <ctime>
#include "renderSystem.h"
#include "gameObject.h"


////////////////////////////////
//constants
const int gameObjectsCountMax = 512;


////////////////////////////////
//class game
class Game
{
public:
	Game();
	
	void setupSystem();
	void initialize();
	bool frame();
	void shutdown();

private:
	void render();
	void update(float dt);

	GameObject* createObject(GameObjectType type, float x, float y, char symbol, consoleColor color, consoleColor bgColor);
	void destroyObject(GameObject* object);

private:
	bool m_isGameActive;
	clock_t m_clockLastFrame;

	renderSystem m_renderSystem;

	GameObject* m_objects[gameObjectsCountMax];

	float m_shipFireCooldownTime;
	float m_alienAmplitudeTime;
};
