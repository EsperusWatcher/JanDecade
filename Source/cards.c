#include "cards.h"

// TODO: should be consequatively called from load cards to fill deck
void addCard(cardList *cardSet, char *pathTexture, int curHp, int maxHp, char *name)
{
    cardList *tmp;
    tmp = malloc(sizeof(cardList));

    if (tmp)
    {
        tmp->card.cardTexture = LoadTexture(pathTexture);
        tmp->card.curHp = curHp;
        tmp->card.maxHp = maxHp;
        strcpy(tmp->card.name, name);

        tmp->nextCard = NULL;
        cardSet->nextCard = tmp;
    }
    else
        printf("error?\n"); // TODO: error detection (????????)
    
}

// Card is removed in case its curHp drops below 0
// It's being founded in list by its number and free'd
void removeCard(cardList *cardSet, int number)
{
    cardList *tmp = getCard(cardSet, number - 1);

    if (cardSet->nextCard != NULL) // Current card is not the head of deck
    {
        cardList *tmp_2 = tmp->nextCard;
        tmp = tmp_2->nextCard;

        free(tmp_2->card.name);
        free(tmp_2);
    }
    else
        printf("[ERROR] Deleting cards from an empty list!!"); // still no error detection...
}

cardList* getCard(cardList *cardSet, int number)
{
    for (int i = 0; i < number && cardSet->nextCard != NULL; i++)
        cardSet = cardSet->nextCard;

    return cardSet;
}

// Called once in the beginning of playing session
// TODO: add consequative load cards call
void initCardSet(cardList *cardSet)
{
    cardSet = malloc(sizeof(cardList));
    cardSet->nextCard = NULL;
}

// Freeing memory, called in the end of each battle
void emptyCardSet(cardList *cardSet)
{
    while(cardSet->nextCard != NULL)
        removeCard(cardSet, 1);
    
    free(cardSet);
}

// Game saving?
void savecardSetFile(cardList *cardSet)
{
    // TODO: open file and save card data in local storage
}

// Game loading?
void loadcardSetFile(cardList *cardSet)
{
    // TODO: open a local data storage (if present) and load card data
}

void formEnemyDeck(cardList *cardSet)
{
    //TODO: random enemy cardSet generation
}