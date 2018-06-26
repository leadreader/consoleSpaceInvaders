#pragma once


//////////////////////////////////
//includes
#include "renderSystem.h"


//////////////////////////////////
//constants
const int levelRows = screenRows;
const int levelColumns = screenColumns;

const float shipSpeed = 35.0;
const float shipFireCooldown = 0.2;
const float shipFasterFireCooldown = 0.1;

const float bulletSpeed = 40.0;
const float bonusSpeed = 20.0;

const float alienAmplitude = 7.0;
const float alienSpeed = 0.23;
const float alienAmplitudeFreeze = 0.0;
const float alienSpeedFreeze = 0.0;


const unsigned char cellSymbol_Ship = 'S';
const unsigned char cellSymbol_Bullet = '|';
const unsigned char cellSymbol_Alien = 'X';
const unsigned char cellSymbol_Alien_Red = 'P';
const unsigned char cellSymbol_Alien_Big = 'B';
const unsigned char cellSymbol_Bonus_DoubleShot = 'D';
const unsigned char cellSymbol_Bonus_Freeze = 'F';
const unsigned char cellSymbol_Bonus_Reload = 'R';
unsigned char cellSymbol_Bonus;

const unsigned char leveldata0[levelRows][levelColumns + 1] =
{
	"                                                                                ",
	"       XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX          ",
	"         X  XXXX XX XXXXXX XXXXXXXXXXXXXXXXXXXXXXX XXXXXX XX XXXX  X            ",
	"       XXXXXXXXX    X XX X X  XXX  XXXXXXX  XXX  X X XX X    XXXXXXXXX          ",
	"            XXXX    X XX X XXXXXXX  XXXXX  XXXXXXX X XX X    XXXX               ",
	"            XXXX           B   XXXXXXXXXXXXXXX   B           XXXX               ",
	"            X  X                XXXXXXXXXXXXX                X  X               ",
	"                                XX  XXXXX  XX                                   ",
	"                                XX  X   X  XX                                   ",
	"                                B           B                                   ",
	"                                                                                ",
	"                                                                                ",
	"                                                                                ",
	"                                                                                ",
	"                                                                                ",
	"                                                                                ",
	"                                                                                ",
	"                                                                                ",
	"                                                                                ",
	"                                                                                ",
	"                                                                                ",
	"                                                                                ",
	"                                                                                ",
	"                                                                                ",
	"                                      S                                         ",
};


///////////////////////////////////////////
//functions 
unsigned char GetRenderCellSymbol(unsigned char cellSymbol)
{
	switch (cellSymbol)
	{
	case cellSymbol_Ship: return 202;
	case cellSymbol_Bullet:return 179;
	case cellSymbol_Alien:return 2;
	case cellSymbol_Alien_Big:return 2;
	case cellSymbol_Bonus_DoubleShot:return 68;
	case cellSymbol_Bonus_Freeze:return 70;
	case cellSymbol_Bonus_Reload:return 82;
	case cellSymbol_Alien_Red:return 2;
	}
	return '?';
}

consoleColor GetRenderCellSymbolColor(unsigned char cellSymbol)
{
	switch (cellSymbol)
	{
	case cellSymbol_Ship: return consoleColor_White;
	case cellSymbol_Bullet: return consoleColor_Red;
	case cellSymbol_Alien:return consoleColor_Green;
	case cellSymbol_Alien_Big:return consoleColor_DarkMagenta;
	case cellSymbol_Bonus_DoubleShot: return consoleColor_Cyan;
	case cellSymbol_Bonus_Freeze: return consoleColor_Cyan;
	case cellSymbol_Bonus_Reload: return consoleColor_Cyan;
	case cellSymbol_Alien_Red:return consoleColor_Red;
	}
	return consoleColor_Gray;
}

consoleColor GetRenderCellSymbolBackgroundColor(unsigned char cellSymbol)
{
	switch (cellSymbol)
	{
	case cellSymbol_Ship: return consoleColor_DarkGray;
	}

	return consoleColor_Black;
}