#include "map.h"

void mapLoop(enum gameState *state)
{
    InitAudioDevice();
    SetMasterVolume(10);
    Sound bgMusic = LoadSound("../Music/Elevator_music.mp3");
    PlaySound(bgMusic);

    //debugStart();
    Map mainmap;
    PlayerState* player = (PlayerState*)malloc(sizeof(PlayerState));
    player->model.x = 0;
    player->model.y = 0;
    player->model.width = 50;
    player->model.height = 50;
    
    mainmap.bg.x = 0;
    mainmap.bg.y = 0;
    mainmap.bg.width = GetScreenWidth();
    mainmap.bg.height = GetScreenHeight();

    mainmap.bgTexture = LoadTexture("../Textures/Map/map_BG.png");
    mainmap.roads = LoadTexture("../Textures/Map/map_Road2.png");

    Road firstRoad = processRoad("Road2");
    SetShapesTexture(mainmap.bgTexture, mainmap.bg);

    startMovement(player, &firstRoad);

    while (*state == MAP)
    {
        updateMovement(player);

        BeginDrawing();

        ClearBackground(PINK);
        DrawRectangleRec(mainmap.bg, WHITE);
        DrawTexture(mainmap.roads, 0, 0, BLACK);
        DrawRectangleRec(player->model, RED);
        DrawText("MAP", 100, 100, 60, WHITE);

        EndDrawing();

        if (WindowShouldClose())
            *state = EXIT;

        if (IsKeyPressed(KEY_D))
            *state = BATTLE;
    }

    CloseAudioDevice();
}

void startMovement(PlayerState *plSt, Road *road)
{
    plSt->currentPosInMap = 0;
    plSt->road = road;
    plSt->model.x = road->firstPoint.x;
    plSt->model.y = road->firstPoint.y;
}

void updateMovement(PlayerState *plSt)
{
    plSt->currentPosInMap++;
    int halfOfSizeX = plSt->model.width / 2;
    int halfOfSizeY = plSt->model.height / 2;
    plSt->model.x = plSt->road->points[plSt->currentPosInMap].x - halfOfSizeX;
    plSt->model.y = plSt->road->points[plSt->currentPosInMap].y - halfOfSizeY;
}

void drawPlayer(PlayerState *plSt)
{
    //DrawRectanglePro(plSt->model, plSt->pos, 0.0f, RED);
}

Road processRoad(char *roadname)
{
    Road road;
    road.name = (char *)malloc(strlen(roadname) * sizeof(char));

    strcpy(road.name, roadname);
    FILE *fp = fopen("roads.data", "r");
    if (fp == NULL)
    {
        printf("Cannot open file roads.data\n");
        return road;
    }

    char roadnamebuf[MAX_ROAD_NAME] = "";
    char buf;
    int x1buf, x2buf, y1buf, y2buf, width, height;

    while (!feof(fp))
    {
        fscanf(fp, "%s %d %d %d %d %d%c%d", roadnamebuf, &x1buf, &y1buf, &x2buf, &y2buf, &width, &buf, &height);

        if (strcmp(roadname, roadnamebuf) == 0)
        {
            road.firstPoint.x = x1buf;
            road.firstPoint.y = y1buf;
            road.secondPoint.x = x2buf;
            road.secondPoint.y = y2buf;
            road.pointCount = 0;
            break;
        }
    }
    fclose(fp);

    Image Roads = LoadImage("../Textures/Map/Road2.png");
    Color *RoadsPixels = GetImageData(Roads);
    UnloadImage(Roads);

    int startpointIndex = coordToIndexConvert(road.firstPoint.x, road.firstPoint.y, width, height);
    int endpointIndex = coordToIndexConvert(road.secondPoint.x, road.secondPoint.y, width, height);
    Vector2 curPos, prevPos;
    curPos.x = road.firstPoint.x;
    curPos.y = road.firstPoint.y;
    prevPos.x = curPos.x;
    prevPos.y = curPos.y;

    while (startpointIndex != endpointIndex)
    {
        Vector2 topLeft;
        topLeft.x = curPos.x - 1; // top left in *checkable* square
        topLeft.y = curPos.y - 1; // same

        int flagExitloop = 0;

        // Take color by pixel coordinate. Go from top left to bottom right
        for (int i = 0; i < 3; i++) // for x
        {
            for (int j = 0; j < 3; j++) // for y
            {
                Vector2 curPixelPos;
                curPixelPos.x = topLeft.x + i;
                curPixelPos.y = topLeft.y + j;

                int firstBool = vectorEquation(&curPos, &curPixelPos);
                int secondBool = vectorEquation(&prevPos, &curPixelPos);

                if ((firstBool != 1) && (secondBool != 1))
                {

                    int index = coordToIndexConvert(curPixelPos.x, curPixelPos.y, width, height); // Taking index by pixel coordinates
                    startpointIndex = index;
                    Color curPixel = RoadsPixels[index]; // Taking Pixel color
                    if (curPixel.r == 0)                 // if black
                    {
                        prevPos.x = curPos.x; // update previous position
                        prevPos.y = curPos.y; // same
                        curPos.x = curPixelPos.x;
                        curPos.y = curPixelPos.y;
                        flagExitloop = 1;
                        break;
                    }
                }
            }
            if (flagExitloop == 1)
                break;
        }

        if (road.pointCount == 0) // if first time, then allocate memory
        {
            road.points = (Vector2 *)malloc(sizeof(Vector2));
            road.points[0] = curPos;
            road.pointCount++;
        }
        else // else re-allocate memory
        {
            road.points = realloc(road.points, sizeof(Vector2) * (road.pointCount + 1));
            road.points[road.pointCount] = curPos;
            road.pointCount++;
        }
    }
    return road;
}

int coordToIndexConvert(int x, int y, int width, int height)
{
    if (x > width || y > height)
    {
        return -1; // This pos out of image
    }

    int result = ((width)*y) + x;

    if (result > width * height)
    {
        return -1; // This position doesnot exist
    }
    return result;
}