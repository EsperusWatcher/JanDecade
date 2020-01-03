#include "map.h"

void mapLoop(enum gameState *state)
{
    while (*state == MAP)
    {
        BeginDrawing();

        ClearBackground(PINK);
        DrawText("MAP", 100, 100, 60, WHITE);

        EndDrawing();

        //printf("Hoho ho %d\n", *state);

        if (WindowShouldClose())
            *state = EXIT;

        if (IsKeyPressed(KEY_D))
            *state = BATTLE;

    }

}
