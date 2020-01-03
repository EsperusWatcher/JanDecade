#ifndef MATH_H
#define MATH_H

#include "game.h"

// if equals return 1, else return everything
int VectorEq(Vector2 *first, Vector2 *second)
{
    if (first->x == second->x && first->y == second->y)
    {
        return 1;
    }
    return 0;
}

#endif