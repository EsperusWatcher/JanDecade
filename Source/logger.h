#ifndef LOGGER_H
#define LOGGER_H

#include "game.h"

void debugInfoVector2(Vector2 vec, char *additionalText);

void debugInfoInt(int number, char *additionalText);

void debugInfoText(char *additionalText);

void debugStart();

#endif