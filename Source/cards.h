#ifndef CARDS_H
#define CARDS_H

#include "game.h"

typedef struct card card;
typedef struct cardList cardList;

struct cardList // Linked list to store current cards
{
    card card;
    cardList *nextCard;
};

struct card
{
    Texture2D cardTexture;
    int dmgType;
    int number; // Numbeer of card in hand
    int curHp; // Also serves as damage
    int maxHp;
    char *name;
};

void addCard(cardList *cardSet, char *pathTexture, int curHp, int maxHp, char *name);
void removeCard(cardList *cardSet, int number);
cardList* getCard(cardList *cardSet, int number);
void initCardSet(cardList *cardSet);
void emptyCardSet(cardList *cardSet);
void savecardSetFile(cardList *cardSet);
void loadcardSetFile(cardList *cardSet);
void formEnemyDeck(cardList *cardSet);

#endif