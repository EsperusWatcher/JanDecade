#ifndef LIST_H
#define LIST_H

#include <stdlib.h>
#include "game.h"
#include "logger.h"

typedef struct Node
{
    void *data;
    struct Node *prev;
    struct Node *next;
} Node;

typedef struct List
{
    Node *Head;
    Node *Tail;
    int count;
} List;

List createList();

void pushBackNode(List *list, void *data);

void *getNodeByIndex(List *list, int index);

void deleteNode(List *list, int index);

#endif