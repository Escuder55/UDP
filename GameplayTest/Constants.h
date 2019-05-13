#pragma once

#define SCREEN_WIDTH 960
#define SCREEN_HEIGHT 540

/////////////// POSICION PUERTAS
	//////UP
	#define DOOR_UP_POS_X 450
	#define DOOR_UP_POS_Y 6
	//////RIGHT
	#define DOOR_RIGHT_POS_X 885
	#define DOOR_RIGHT_POS_Y 240
	//////DOWN
	#define DOOR_DOWN_POS_X 450
	#define DOOR_DOWN_POS_Y 465
	//////LEFT
	#define DOOR_LEFT_POS_X 6
	#define DOOR_LEFT_POS_Y 240

/////////////// TAMA�O SPRITE DE PERSONAJE
	#define SPRITE_CHARACTER_WIDTH 52
	#define SPRITE_CHARACTER_HEIGHT 72

enum Direcciones
{
	NONE,
	UP,
	RIGHT,
	DOWN,
	LEFT
};


enum CharacterType
{
	ZERO,
	ONE,
	TWO,
	THREE,
	FOUR,
	FIVE,
	SIX,
	SEVEN,
	EIGHT
};

enum TypeScene
{
	FIRST_CHOICE,
	LOG_IN,
	SIGN_UP,
	MENU,
	MAPS,
	PLAY,
	GOTO_FIRST_CHOICE,
	GOTO_LOG_IN,
	GOTO_SIGN_UP,
	GOTO_MENU,
	GOTO_MAPS,
	GOTO_PLAY,
	EXIT

};