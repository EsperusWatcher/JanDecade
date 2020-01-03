#include "game.h"
#include "map.h"
#include "battle.h"

void initScreen(struct Screen* Screen);

int main()
{
	struct Screen gameScreen;
	initScreen(&gameScreen);

	enum gameState gameState = MAP; // Current behaviour

	InitWindow(gameScreen.screenWidth, gameScreen.screenHeight, "JanDecade");
	SetTargetFPS(60);

	while(!WindowShouldClose() && gameState != EXIT) // mainloop
	{
		switch (gameState)
		{
			case MAP:
				mapLoop(&gameState);
				break;
			
			case BATTLE:
				battleLoop(&gameState);
				break; 
			default:
				break;
		}
	}

	CloseWindow();

	return 0;
}

void initScreen(struct Screen* Screen)
{
	Screen->screenHeight = 1024;
	Screen->screenWidth = 1640;
}
