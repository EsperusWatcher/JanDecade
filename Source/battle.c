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


void battleLoop(enum gameState *state)
{
    static Texture2D battleBackground;
    battleBackground = LoadTexture("../Textures/Battlefield.png");

    // TODO: maybe move it somewhere else??
    cardList playerCardSet;
    initCardSet(&playerCardSet);
    setPlayerCards_tmp(&playerCardSet); // Testing purposes only
    
    while (*state == BATTLE)
    {
        BeginDrawing();

        DrawTexture(battleBackground, 0, 0, WHITE);
        DrawText("VS", 820, 512, 120, RED);

        EndDrawing();
        
        if (IsKeyPressed(KEY_D))
            *state = MAP;
        
        if (WindowShouldClose())
            *state = EXIT;
    }

}

// Testing purposes only
void setPlayerCards_tmp(cardList *playerCardSet)
{

}