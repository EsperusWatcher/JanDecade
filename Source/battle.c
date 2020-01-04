#include "battle.h"

// ------ GENERAL INFO -------
// Records of cards in hand/stock |
// Records of cards in bot's hand | --> Amount of cards, 
// Enemy info ---> Event type
// Loss consequences ---> Equipment tracker

// ------- Individual Cards ------
// store cur_hp/max_atk on card
// store type of damage
//  --- Card GUI
//  |-------------------------------------|
//  |Type of damage ----- cur_hp / max_hp |
//  |                                     |
//  |             / _   _\                |
//  |       .<---|  o  o | --->.          |
//  |            \   0  /                 |
//  |             | | |                   |
//  |             | | \                   |
//  |                                     |
//  |             NAME                    |
//  |-------------------------------------|

// ------- Battle --------
// ?? Battlefield type ---> Refer to map province
// compare hp and atk of two cards, process results, update card lists
// check for win condition each turn, call for events in caseof

// ------- GUI --------
// ?? Enemy / Your Morale bars
// Surrender button
// ?? Options
// Display current cards 

// BIG TODO LIST:
// 1) Retrieve card info (currently using test version) from player data block
// --- cards are stored in a inked list form
// ---
// 2) Make random enemy cards generation
// ---
// 3) Implement core game mechanics (cards fighting, hp decreasing, deck burning e.t.c.)
// ---
// 4) Make random enemy card selection (in ongoing match)
// ---
// 5) Make condition rules for win/defeat situation, make preps for passing events further
// ---
// 6) Form each card's graphical interface (for displaying later)
// ---
// 7) Set up battlefield
// ---
// 8) load GUI over battlefield (includeing cards)

// Global vars to keep track on curently selected card
int SelectedCardFlag = FALSE; // If card was selected for battle
struct card* SelectedCardPointer = NULL;
Vector2 SelectedCardInitialPosition; // Return it to its original place

void battleLoop(enum gameState *state)
{
    srand(time(NULL));
    static Texture2D battleBackground;
    battleBackground = LoadTexture("../Textures/Battlefield.png");

    // TODO: maybe move it somewhere else??
    cardList *playerCardSet;
    initCardSet(&playerCardSet);
    setPlayerCards_tmp(&playerCardSet);
    arrangePlayerCardsOnField(&playerCardSet);

    while (*state == BATTLE)
    {
        BeginDrawing();

        DrawTexture(battleBackground, 0, 0, WHITE);
        drawPlayerCards(&playerCardSet);

        if (SelectedCardFlag == TRUE)
            drawBattleHUD();

        EndDrawing();
        
        if (IsKeyPressed(KEY_D))
            *state = MAP;
        
        if (WindowShouldClose())
            *state = EXIT;

        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
        {
            detectCardClick(&playerCardSet);

            if (SelectedCardFlag == TRUE)
            {
                detectReadyButtonClick();
            }
        }
    }

    emptyCardSet(&playerCardSet);
    *state = MAP;
}

// Testing purposes only
void setPlayerCards_tmp(cardList **playerCardSet) 
{
    // TODO: related to future version: this should be automatic based on stored data
    addCard(playerCardSet, "../Textures/Archer_1.png", AGILITY, 3, 3, "Alfredo");
    addCard(playerCardSet, "../Textures/Soldier_1.png", STRENGTH, 5, 6, "Ivan");
    addCard(playerCardSet, "../Textures/Spearman_1.png", CHARISMA, 4, 4, "Xin Yang");
    addCard(playerCardSet, "../Textures/Soldier_1.png", STRENGTH, 5, 6, "Ivan");
    addCard(playerCardSet, "../Textures/Spearman_1.png", CHARISMA, 4, 4, "Xin Yang");
}

void arrangePlayerCardsOnField(cardList **playerCardSet)
{
    // TODO: make this non-constant
    int curX = PLAYER_CARDS_DRAWING_POSITION_START_X;
    int curY = PLAYER_CARDS_DRAWING_POSITION_START_Y;
    int step = PLAYER_CARDS_DRAWING_POSITION_STEP; // Distance between each card

    cardList *currCard = (*playerCardSet)->nextCard;

    while (currCard != NULL)
    {
        currCard->card.posX = curX;
        currCard->card.posY = curY;
        currCard = currCard->nextCard;
        curX -= step;
    }
}

void drawPlayerCards(cardList **playerCardSet)
{
    cardList *currCard = (*playerCardSet)->nextCard;
    Color hpColor;

    while (currCard != NULL)
    {
        if (currCard->card.curHp < currCard->card.maxHp)
            hpColor = RED;
        else
            hpColor = BLACK;

        DrawTexture(currCard->card.cardTexture, currCard->card.posX, currCard->card.posY, WHITE);

        switch (currCard->card.dmgType)
        {
            case AGILITY:
                DrawText("AGL", currCard->card.posX + 5, currCard->card.posY + 5, 10, BLACK);
                break;
            case STRENGTH:
                DrawText("STR", currCard->card.posX + 5, currCard->card.posY + 5, 10, BLACK);
                break;
            case CHARISMA:
                DrawText("CHA", currCard->card.posX + 5, currCard->card.posY + 5, 10, BLACK);
                break;

            default: 
                printf("[ERROR] Mising card info\n"); // errrrrorrrrrr detectiooooooon...
                break;
        }

        char hpString[CARD_MAX_HP];
        DrawText(currCard->card.name, currCard->card.posX + PLAYER_CARD_SIZE_X / 2 - strlen(currCard->card.name) * 3,
                 currCard->card.posY + PLAYER_CARD_SIZE_Y - 15, 10, BLACK);

        DrawText(getIntToString(currCard->card.curHp, hpString), currCard->card.posX + PLAYER_CARD_SIZE_X - 25,
                currCard->card.posY + 5, 10, hpColor);

        DrawText(" / ", currCard->card.posX + PLAYER_CARD_SIZE_X - 22, currCard->card.posY + 5, 10, BLACK);
        
        DrawText(getIntToString(currCard->card.maxHp, hpString), currCard->card.posX + PLAYER_CARD_SIZE_X - 10,
            currCard->card.posY + 5, 10, BLACK);

        currCard = currCard->nextCard;
    }
}

void drawBattleHUD()
{
    Vector2 startButtonPos;
    startButtonPos.x = PLAYER_FIGHTER_CENTERED_X - BUTTON_SIZE_WIDTH / 4;
    startButtonPos.y = PLAYER_FIGHTER_CENTERED_Y + BUTTON_SIZE_WIDTH * 2 - 60;   
    DrawRectangle(startButtonPos.x, startButtonPos.y, BUTTON_SIZE_WIDTH, BUTTON_SIZE_HEIGHT, DARKGREEN);
    
    DrawText("START", startButtonPos.x + 5, startButtonPos.y + BUTTON_SIZE_HEIGHT / 2 - 15, 30, BLACK);
}

char* getIntToString (int n, char *string)
{
    snprintf( string, CARD_MAX_HP, "%d", n);

    return string;
}

void detectCardClick(cardList **playerCardSet)
{
    cardList *currCard = (*playerCardSet)->nextCard;

    Vector2 mousePos = GetMousePosition();

    while (currCard != NULL)
    {
        if ((currCard->card.posX <= mousePos.x) && (mousePos.x <= currCard->card.posX + PLAYER_CARD_SIZE_X))
            if ((currCard->card.posY <= mousePos.y) && (mousePos.y <= currCard->card.posY + PLAYER_CARD_SIZE_Y))
            {
                cardWasSelectedPlayer(&currCard);
                break;
            }
        currCard = currCard->nextCard;
    }
}

void detectReadyButtonClick()
{
    // makes things happen
}

// Moves selected card to the center of battlefield
void cardWasSelectedPlayer(cardList **playerSelectedCard)
{
    if (SelectedCardFlag == TRUE) // In case another card was selected, returns previous one on its place
    {
        printf("returning %s to its original position\n", SelectedCardPointer->name);
        SelectedCardPointer->posX = SelectedCardInitialPosition.x;
        SelectedCardPointer->posY = SelectedCardInitialPosition.y; 
    }

    printf("Clicked on %s\n", (*playerSelectedCard)->card.name);

    SelectedCardInitialPosition.x = (*playerSelectedCard)->card.posX;
    SelectedCardInitialPosition.y = (*playerSelectedCard)->card.posY;

    (*playerSelectedCard)->card.posX = PLAYER_FIGHTER_CENTERED_X;
    (*playerSelectedCard)->card.posY = PLAYER_FIGHTER_CENTERED_Y;

    SelectedCardPointer = &(*playerSelectedCard)->card;
    printf("Currently selected card: %s\n", SelectedCardPointer->name);

    SelectedCardFlag = TRUE;
}