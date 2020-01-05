#ifndef PLAYER_H
#define PLAYER_H

#include "game.h"
#include "list.h"
#include "cards.h"

typedef struct PlayerCaravan PlayerCaravan;
typedef struct Wagon Wagon;

struct Goods
{
    int gabarites;
    int value;
};

struct Wagon
{
    int capacity;
    int speed;
    int hp;
    List goods;
};

struct PlayerCaravan
{
    unsigned int hp;
    int deckSize;
    cardList *deckList;
    Wagon wagon;
};

void initPlayer(PlayerCaravan *player);
int getPlayerCards(cardList **player); // TODO: make this random

#endif