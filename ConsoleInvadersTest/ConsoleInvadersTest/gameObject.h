#pragma once


///////////////////////////
//includes
#include "renderSystem.h"


///////////////////////////
//enum
enum GameObjectType
{
	GameObjectType_None,
	GameObjectType_Ship,
	GameObjectType_Bullet,
	GameObjectType_Alien,
	GameObjectType_Alien_Big,
	GameObjectType_Bonus_Reload,
	GameObjectType_Bonus_DoubleShot,
	GameObjectType_Bonus_Freeze
};


/////////////////////////
//class gameobject
class GameObject
{
public:
	GameObject();

	void render(renderSystem* rs);
	void update(float dt);

	bool intersects(GameObject* object);


	void setType(GameObjectType type) { m_type = type; }
	GameObjectType getType() { return m_type; }

	void setH(int h) { m_h = h; }
	int getH() { return m_h; }

	void setX(float x) { m_x = x; }
	float getX() { return m_x; }

	void setY(float y) { m_y = y; }
	float getY() { return m_y; }

	void setXSpeed(float xSpeed) { m_xSpeed = xSpeed; }
	float getXSpeed() { return m_xSpeed; }

	void setYSpeed(float ySpeed) { m_ySpeed = ySpeed; }
	float getYSpeed() { return m_ySpeed; }

	void setSymbol(char symbol) { m_symbol = symbol; }
	float getSymbol() { return m_symbol; }

	void setColor(consoleColor color) { m_color = color; }
	consoleColor getColor() { return m_color; }

	void setBackgroundColor(consoleColor backgroundColor) { m_backgroundColor = backgroundColor; }
	consoleColor getBackgroundColor() { return m_backgroundColor; }

private:
	GameObjectType m_type;

	int m_h;
	float m_x;
	float m_y;
	float m_xSpeed;
	float m_ySpeed;

	char m_symbol;
	consoleColor m_color;
	consoleColor m_backgroundColor;
};
