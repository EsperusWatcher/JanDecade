#include "gamemath.h"

int vectorEquation(Vector2 *first, Vector2 *second)
{
    if (first->x == second->x && first->y == second->y)
    {
        return 1;
    }
    return 0;
}