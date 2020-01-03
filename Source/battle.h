#ifndef BATTLE_H
#define BATTLE_H

// aka rock paper scissors
#define STRENGTH 0
#define CHARISMA 1
#define AGILITY 2

#include "game.h"
#include "cards.h"

// TODO: add game states for shifting to victory/defeat and event screens
void battleLoop(enum gameState *state); // Battle loop, ends with defeat, victory or surrender

// TODO: everything, displaying elements of gui over battlefield
void setBattleGUI();

// TODO: requires player module to be written 
void setPlayerCards(); // Should have acces to player block and retrieve info on cards

void setPlayerCards_tmp(); // For testing purposes, WIP

void drawPlayerCards(cardList *cardSet); // Applies GUI on cards and draws them on battlefield

#endif