#ifndef GAME_H
#define GAME_H

#include "raylib.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TRUE 1
#define FALSE 0

// aka rock paper scissors
#define STRENGTH 0
#define CHARISMA 1
#define AGILITY 2

struct Screen
{
	int screenWidth;
	int screenHeight;
};

enum gameState
{
	MAP,
	BATTLE,
	EXIT
};

#endif