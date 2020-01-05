#ifndef BATTLE_H
#define BATTLE_H

// aka rock paper scissors
#define STRENGTH 0
#define CHARISMA 1
#define AGILITY 2

#define PLAYER_FIGHTER_CENTERED_X 970
#define PLAYER_FIGHTER_CENTERED_Y 700
#define PLAYER_CARDS_DRAWING_POSITION_START_X 690
#define PLAYER_CARDS_DRAWING_POSITION_START_Y 900
#define PLAYER_CARDS_DRAWING_POSITION_STEP 140
#define PLAYER_CARD_SIZE_X 80
#define PLAYER_CARD_SIZE_Y 120

#define ENEMY_CARDS_DRAWING_POSITION_START_X 1250
#define ENEMY_CARDS_DRAWING_POSITION_START_Y 20
#define ENEMY_CARDS_DRAWING_POSITION_STEP 140

#define CARD_MAX_HP 30

#define BUTTON_SIZE_WIDTH 120
#define BUTTON_SIZE_HEIGHT 60

#define MIN_FRAMERATE_SPEED 1
#define MAX_FRAMERATE_SPEED 15

#define WIN 1
#define LOSS -1
#define DRAW 0

#define STRING_BUFFER 100

#include "game.h"
#include "cards.h"

// TODO: add game states for shifting to victory/defeat and event screens
void battleLoop(enum gameState *state); // Battle loop, ends with defeat, victory or surrender
void startBattle(struct card *playerCard, struct card *enemyCard, Texture2D battleBackground);

// TODO: everything, displaying elements of gui over battlefield
void setBattleGUI();
void drawBattleHUD(Vector2 *startButtonPos);
void drawCard(struct card *currCard);
int detectButtonClick(Vector2 buttonPos);

// TODO: requires player module to be written 
void setPlayerCards(); // Should have acces to player block and retrieve info on cards

void setPlayerCards_tmp(cardList **playerCardSet);// For testing purposes, WIP

void arrangePlayerCardsOnField(cardList **playerCardSet); // set XY coordinates for each card
void arrangeEnemyCardsOnField(cardList **enemyCardSet);

void drawPlayerCards(cardList **playerCardSet); // Applies GUI on cards and draws them on battlefield
void drawEnemyCards(cardList **enemyCardSet, Texture2D hiddenEnemie);

void detectCardClick(cardList **playerCardSet);
void cardWasSelectedPlayer(cardList **playerSelectedCard);
void enemyPicksCard(cardList **enemyCardSet);
void resetRound();

char* getIntToString (int n, char *string);


#endif