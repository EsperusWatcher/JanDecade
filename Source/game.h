#ifndef GAME_H
#define GAME_H

#include "raylib.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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