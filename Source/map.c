#include "map.h"

void mapLoop(enum gameState *state)
{
    Map mainmap;
    PlayerState player;

    //player.pos =

    mainmap.bg.x = 0;
    mainmap.bg.y = 0;
    mainmap.bg.width = GetScreenWidth();
    mainmap.bg.height = GetScreenHeight();

    mainmap.bgTexture = LoadTexture("../Textures/Map/map_BG.png");
    mainmap.roads = LoadTexture("../Textures/Map/map_Road.png");
    Image Roads = LoadImage("../Textures/Map/map_Road.png");
    Color *RoadsPixels = GetImageData(Roads);

    printf("Sizeof RoadsPixels - %d\n", sizeof(RoadsPixels));
    printf("Sizeof RoadsPixels[0] - %d\n", sizeof(RoadsPixels[0]));
    printf("Sizeof RoadsPixels[0] - %d\n", sizeof(RoadsPixels) / sizeof(RoadsPixels[0]));

    SetShapesTexture(mainmap.bgTexture, mainmap.bg);

    while (*state == MAP)
    {
        BeginDrawing();

        ClearBackground(PINK);

        DrawRectangleRec(mainmap.bg, WHITE);
        DrawText("MAP", 100, 100, 60, WHITE);
        DrawTexture(mainmap.roads, 0, 0, WHITE);

        updateMovement(&player, RoadsPixels);
        drawPlayer(&player);

        EndDrawing();

        if (WindowShouldClose())
            *state = EXIT;

        if (IsKeyPressed(KEY_D))
            *state = BATTLE;
    }
}

void updateMovement(PlayerState *plSt, Color *roads, MapState *mapSt)
{
    struct stPixel
    {
        Color color;
        Vector2 pos;
        int count; // Number of white blocks around;
    };

    struct stPixel buf[9];
    Vector2 origin, destination, position, prevposition;
    origin = mapSt->current->pos;
    destination = mapSt->destination->pos;
    position = plSt->pos;
    prevposition = plSt->prevpos;

    enum cases
    {
        ONE,   // X1 >= X2; Y1 >= Y2
        TWO,   // X1 >= X2; Y1 < Y2
        THREE, // X1 < X2; Y1 >= Y2
        FOUR   // X1 < X2; Y1 < Y2
    };

    enum cases curCase;

    if (origin.x >= destination.x)
    {
        if (origin.y >= destination.y)
            curCase = ONE;
        else
            curCase = TWO;
    }
    else
    {
        if (origin.y >= destination.y)
            curCase = THREE;
        else
            curCase = FOUR;
    }

    for (int i = 0; i < 9; i++)
    {
        int x, y;
        x = buf[i].pos.x - 1;
        y = buf[i].pos.y - 1;
        int arr[9] = {
            ((GetScreenWidth() + 1) * (position.x - 1)) + ((position.y - 1) + 1) - 1,
            ((GetScreenWidth() + 1) * (position.x)) + ((position.y - 1) + 1) - 1,
            ((GetScreenWidth() + 1) * (position.x + 1)) + ((position.y - 1) + 1) - 1,

            ((GetScreenWidth() + 1) * (position.x - 1)) + ((position.y) + 1) - 1,
            ((GetScreenWidth() + 1) * (position.x)) + ((position.y) + 1) - 1,
            ((GetScreenWidth() + 1) * (position.x + 1)) + ((position.y) + 1) - 1,

            ((GetScreenWidth() + 1) * (position.x - 1)) + ((position.y + 1) + 1) - 1,
            ((GetScreenWidth() + 1) * (position.x)) + ((position.y + 1) + 1) - 1,
            ((GetScreenWidth() + 1) * (position.x + 1)) + ((position.y + 1) + 1) - 1,
        };
        
        if (roads[arr[0]].r == 0)
        {
        }
    }

    for (int i = 0; i < 9; i++)
    {
        if ((!VectorEq(&position, &buf[i]) || !VectorEq(&prevposition, &buf[i])) && buf[i].color.r == 0)
        {
            int x, y;
            x = buf[i].pos.x - 1;
            y = buf[i].pos.y - 1;
            for (int j = 0; j < 9; j++)
            {
                int index = ((GetScreenWidth() + 1) * buf[j].pos.x) + (buf[j].pos.y + 1) - 1;
            }
        }
    }
}

void drawPlayer(PlayerState *plSt)
{
    DrawRectanglePro(plSt->model, plSt->pos, 0.0f, RED);
}