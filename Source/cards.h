#ifndef CARDS_H
#define CARDS_H

#include "game.h"

typedef struct cardList cardList;

struct card
{
    Texture2D cardTexture;
    int isVisible; // Used to display enemies if they reveal themselves
    int dmgType;
    int number; // Numbeer of card in hand
    int curHp; // Also serves as damage
    int maxHp;
    Vector2 pos;
    char *name;
};

struct cardList // Linked list to store current cards
{
    struct card card;
    cardList *nextCard;
};

void addCard(cardList **cardSet, char *pathTexture, int dmgType, int curHp, int maxHp, int id, char *name);
void removeCard(cardList **cardSet, int number);
cardList* getCard(cardList **cardSet, int number);
cardList* getLast(cardList **cardSet);
void initCardSet(cardList **cardSet);
void emptyCardSet(cardList **cardSet);
void savecardSetFile(cardList **cardSet);
void loadcardSetFile(cardList **cardSet);
void makeRandomCard(cardList **cardSet);
void initEnemyRandomDeck(cardList **enemyCardSet, int amount);

#endif