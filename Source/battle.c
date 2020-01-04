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

int BattleOn = FALSE;

// Global vars to keep track on curently selected card
int SelectedCardFlag = FALSE; // If card was selected for battle
struct card* SelectedCardPointer = NULL;
Vector2 SelectedCardInitialPosition; // Return it to its original place

void battleLoop(enum gameState *state)
{
    srand(time(NULL));
    static Texture2D battleBackground;
    battleBackground = LoadTexture("../Textures/Battlefield.png");
    Texture2D enemyCard;
    enemyCard = LoadTexture("../Textures/Unknown_enemy.png");

    int battleResult = -10;

    // TODO: maybe move it somewhere else??
    cardList *playerCardSet;
    cardList *enemyCardSet;
    initCardSet(&playerCardSet);
    initCardSet(&enemyCardSet);
    setPlayerCards_tmp(&playerCardSet);
    arrangePlayerCardsOnField(&playerCardSet);

    makeRandomCard(&enemyCardSet);
    enemyCardSet->nextCard->card.posX = PLAYER_FIGHTER_CENTERED_X;
    enemyCardSet->nextCard->card.posY = PLAYER_FIGHTER_CENTERED_Y - PLAYER_CARD_SIZE_Y * 5;

    Vector2 readyButton;

    while (*state == BATTLE)
    {
        BeginDrawing();

        DrawTexture(battleBackground, 0, 0, WHITE);
        drawPlayerCards(&playerCardSet);

        if (SelectedCardFlag == TRUE)
        {
            drawBattleHUD(&readyButton);

            //If player selected his fighter unknown entity appears
            DrawTexture(enemyCard, PLAYER_FIGHTER_CENTERED_X, PLAYER_FIGHTER_CENTERED_Y - PLAYER_CARD_SIZE_Y * 5, WHITE);
        }
        
        if (BattleOn)
        {
            startBattle(SelectedCardPointer, &enemyCardSet->nextCard->card, battleBackground);

            if (SelectedCardPointer->curHp < 1)
                removeCard(&playerCardSet, SelectedCardPointer->number);

            if (enemyCardSet->nextCard->card.curHp < 1)
                removeCard(&enemyCardSet, 1);
            
            if (playerCardSet->nextCard == NULL)
                battleResult = LOSS;

            if (enemyCardSet->nextCard == NULL)
                battleResult = WIN;

            if (enemyCardSet->nextCard == NULL && playerCardSet->nextCard == NULL)
                battleResult = DRAW;

            // TODO: Here should be a resulting window of event that triggered this fight

            // Testing purposes:
            switch (battleResult)
            {
                case WIN:
                    DrawText("CONGRATULATIONS!!!!", 100, 100, 100, GOLD);
                    break;
                case LOSS:
                    DrawText("We'll get 'em next time, boiz", 100, 100, 100, DARKPURPLE);
                    break;
                case DRAW:
                    DrawText("Well, it seems we both lost today", 100, 100, 100, GREEN);
                    break;
                default:
                    resetRound(&playerCardSet);
                    break;
            }
        }

        EndDrawing();

        if (WindowShouldClose())
            *state = EXIT;


        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            detectCardClick(&playerCardSet);

            if (SelectedCardFlag == TRUE)
                if (detectButtonClick(readyButton))
                {
                    printf("Start clicked\n");
                    BattleOn = TRUE;
                }
        }
    }

    emptyCardSet(&enemyCardSet);
    emptyCardSet(&playerCardSet);

    UnloadTexture(enemyCard);
    UnloadTexture(battleBackground);
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

    while (currCard != NULL)
    {
        drawCard(&currCard->card);
        currCard = currCard->nextCard;
    }
}

void drawCard(struct card *currCard)
{
    Color hpColor;
    if (currCard->curHp < currCard->maxHp)
        hpColor = RED;
    else
        hpColor = BLACK;

    DrawTexture(currCard->cardTexture, currCard->posX, currCard->posY, WHITE);

    switch (currCard->dmgType)
    {
        case AGILITY:
            DrawText("AGL", currCard->posX + 5, currCard->posY + 5, 10, BLACK);
            break;
        case STRENGTH:
            DrawText("STR", currCard->posX + 5, currCard->posY + 5, 10, BLACK);
            break;
        case CHARISMA:
            DrawText("CHA", currCard->posX + 5, currCard->posY + 5, 10, BLACK);
            break;

        default: 
            printf("[ERROR] Mising card info\n"); // errrrrorrrrrr detectiooooooon...
            break;
    }

    char hpString[CARD_MAX_HP];
    DrawText(currCard->name, currCard->posX + PLAYER_CARD_SIZE_X / 2 - strlen(currCard->name) * 3,
                currCard->posY + PLAYER_CARD_SIZE_Y - 15, 10, BLACK);

    DrawText(getIntToString(currCard->curHp, hpString), currCard->posX + PLAYER_CARD_SIZE_X - 25,
            currCard->posY + 5, 10, hpColor);

    DrawText(" / ", currCard->posX + PLAYER_CARD_SIZE_X - 22, currCard->posY + 5, 10, BLACK);
    
    DrawText(getIntToString(currCard->maxHp, hpString), currCard->posX + PLAYER_CARD_SIZE_X - 10,
        currCard->posY + 5, 10, BLACK);
}

void drawBattleHUD(Vector2 *startButtonPos)
{
    startButtonPos->x = PLAYER_FIGHTER_CENTERED_X - BUTTON_SIZE_WIDTH / 4;
    startButtonPos->y = PLAYER_FIGHTER_CENTERED_Y + BUTTON_SIZE_WIDTH * 2 - 60;   
    DrawRectangle(startButtonPos->x, startButtonPos->y, BUTTON_SIZE_WIDTH, BUTTON_SIZE_HEIGHT, DARKGREEN);
    
    DrawText("START", startButtonPos->x + 5, startButtonPos->y + BUTTON_SIZE_HEIGHT / 2 - 15, 30, BLACK);
    DrawText("VS", PLAYER_FIGHTER_CENTERED_X - 20, PLAYER_FIGHTER_CENTERED_Y - PLAYER_CARD_SIZE_Y * 2, 75, RED);
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

int detectButtonClick(Vector2 buttonPos)
{
    Vector2 mousePos = GetMousePosition();

    if ((buttonPos.x <= mousePos.x) && (mousePos.x <= buttonPos.x + BUTTON_SIZE_WIDTH))
    {
        if ((buttonPos.y <= mousePos.y) && (mousePos.y <= buttonPos.y + BUTTON_SIZE_HEIGHT))
            return TRUE;
        else
            return FALSE;
    }
    else
        return FALSE;
}

void startBattle(struct card *playerCard, struct card *enemyCard, Texture2D battleBackground)
{
    EndDrawing();
    printf("Battle started\n");
    int animPlayed = FALSE;
    int isFight = TRUE;
    Texture2D EnemyReveal = LoadTexture("../Textures/Unknown_enemy_reveal.png");
    
    Vector2 animPos;
    animPos.x = enemyCard->posX;
    animPos.y = enemyCard->posY;

    Rectangle frameRec = { 0.0f, 0.0f, (float)EnemyReveal.width / 11, (float)EnemyReveal.height };
    int currentFrame = 0;
    int framesCounter = 0;
    int framesSpeed = 4;

    while (isFight)
    {
        BeginDrawing();
        DrawTexture(battleBackground, 0, 0, WHITE);
        framesCounter++;

        if (framesCounter >= (60 / framesSpeed))
        {
            printf("frame: %d\n", currentFrame);
            framesCounter = 0;
            currentFrame++;

            if (currentFrame > 10)
            {
                animPlayed = TRUE;
                enemyCard->posY += (float)currentFrame;
                playerCard->posY -= (float)currentFrame;

                if (enemyCard->posY + PLAYER_CARD_SIZE_Y >= playerCard->posY)
                {
                    int savedDamage = playerCard->curHp;

                    switch (enemyCard->dmgType)
                    {
                        case STRENGTH:
                            switch (playerCard->dmgType)
                            {
                                case STRENGTH:
                                    playerCard->curHp -= enemyCard->curHp;
                                    enemyCard->curHp -= savedDamage;
                                    break;
                                case AGILITY:
                                    playerCard->curHp -= enemyCard->curHp * 2;
                                    enemyCard->curHp -= (savedDamage / 2);
                                    break;

                                case CHARISMA:
                                    playerCard->curHp -= enemyCard->curHp / 2;
                                    enemyCard->curHp -= savedDamage * 2;
                                    break;

                                default: 
                                    break;
                            }
                            break;
                        
                        case AGILITY:
                            switch (playerCard->dmgType)
                            {
                                case STRENGTH:
                                    playerCard->curHp -= enemyCard->curHp / 2;
                                    enemyCard->curHp -= savedDamage * 2;
                                    break;
                                case AGILITY:
                                    playerCard->curHp -= enemyCard->curHp;
                                    enemyCard->curHp -= savedDamage;
                                    break;

                                case CHARISMA:
                                    playerCard->curHp -= enemyCard->curHp * 2;
                                    enemyCard->curHp -= savedDamage / 2;
                                    break;

                                default: 
                                    break;
                            }
                            break;

                        case CHARISMA:
                            switch (playerCard->dmgType)
                            {
                                case STRENGTH:
                                    playerCard->curHp -= enemyCard->curHp * 2;
                                    enemyCard->curHp -= savedDamage / 2;
                                    break;
                                case AGILITY:
                                    playerCard->curHp -= enemyCard->curHp / 2;
                                    enemyCard->curHp -= savedDamage * 2;
                                    break;

                                case CHARISMA:
                                    playerCard->curHp -= enemyCard->curHp;
                                    enemyCard->curHp -= savedDamage;
                                    break;

                                default: 
                                    break;
                            }
                            break;
                        default:
                            break;
                    }

                    isFight = FALSE;
                }
            }

            frameRec.x = (float)currentFrame * (float)EnemyReveal.width / 11;
        }

        if (!animPlayed)
        {
            DrawTextureRec(EnemyReveal, frameRec, animPos, WHITE);
            drawCard(playerCard);
        }
        else
        {
            drawCard(enemyCard);
            drawCard(playerCard);
        }
        
        EndDrawing();
    }

    BattleOn = FALSE;
    UnloadTexture(EnemyReveal);
    BeginDrawing();
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

void resetRound(cardList **playerCardSet)
{
    arrangePlayerCardsOnField(playerCardSet);
    SelectedCardPointer = NULL;
    SelectedCardFlag = FALSE;
}