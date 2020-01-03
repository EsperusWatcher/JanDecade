#include "battle.h"

void battleLoop(enum gameState *state)
{
    while (*state == BATTLE)
    {
        printf("WAAAGH!!\n");
        BeginDrawing();

        ClearBackground(BLACK);
        DrawText("MAP", 100, 100, 60, RED);

        EndDrawing();
        
        if (IsKeyPressed(KEY_D))
            *state = MAP;
        
        if (WindowShouldClose())
            *state = EXIT;
    }

}