#include "game.h"
#include "map.h"
#include "battle.h"
#include "player.h"

void initScreen(struct Screen* Screen);

int main()
{
    srand(time(NULL));
	struct Screen gameScreen;
	initScreen(&gameScreen);

	enum gameState gameState = MAP; // Current behaviour

	InitWindow(gameScreen.screenWidth, gameScreen.screenHeight, "JanDecade");
	SetTargetFPS(60);
	
	PlayerCaravan player;
	initPlayer(&player);

	while(!WindowShouldClose() && gameState != EXIT) // mainloop
	{
		switch (gameState)
		{
			case MAP:
				mapLoop(&gameState);
				break;
			
			case BATTLE:
				initCardSet(&player.deckList);
				player.deckSize = getPlayerCards(&player.deckList);
				battleLoop(&gameState, &player);
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
	Screen->screenWidth = 1920;
	Screen->screenHeight = 1080;
}
