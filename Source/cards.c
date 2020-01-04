#include "cards.h"

// TODO: should be consequatively called from load cards to fill deck
void addCard(cardList **cardSet, char *pathTexture, int dmgType, int curHp, int maxHp, char *name)
{
    cardList *tmp;
    cardList *last = getLast(cardSet);    

    tmp = (cardList *)malloc(sizeof(cardList));

    if (tmp)
    {
        tmp->card.cardTexture = LoadTexture(pathTexture);
        tmp->card.number = (*cardSet)->card.number + 1;
        tmp->card.dmgType = dmgType;
        tmp->card.curHp = curHp;
        tmp->card.maxHp = maxHp;
        tmp->card.name = malloc(strlen(name));
        strcpy(tmp->card.name, name);

        tmp->nextCard = NULL;
        last->nextCard = tmp;
    }
    else
        printf("error?\n"); // TODO: error detection (????????)
}

cardList* getLast(cardList **cardSet)
{
    cardList *tmp = (*cardSet);
    if ((*cardSet)->nextCard != NULL)
    {
        while (tmp->nextCard != NULL)
            tmp = tmp->nextCard;
    }

    return tmp;
}

// Card is removed in case its curHp drops below 0
// It's being founded in list by its number and free'd
void removeCard(cardList **cardSet, int number)
{
    cardList *del_tmp = getCard(cardSet, number); // Gets previous node
    
    if (del_tmp->nextCard != NULL)
    {
        printf("Deleting %s\n", del_tmp->nextCard->card.name);
        cardList *save = del_tmp->nextCard->nextCard;

        free(del_tmp->nextCard->card.name);
        free(del_tmp->nextCard);

        del_tmp->nextCard = save;
    }
    else
        printf("Deleting unknown element?\n"); // Still no error detection...
}

// Called in case card dies and has to be removed from deck (^^^^)
cardList* getCard(cardList **cardSet, int number)
{
    cardList *tmp = (*cardSet);

    while (tmp != NULL && tmp->nextCard->card.number != number)
        tmp = tmp->nextCard;

    return tmp;
}

// Called once in the beginning of playing session
// TODO: add consequative load cards call
void initCardSet(cardList **cardSet)
{
    (*cardSet) = (cardList *)malloc(sizeof(cardList));
    (*cardSet)->nextCard = NULL;
    (*cardSet)->card.number = 0;
    (*cardSet)->card.name = "root";
}

// Freeing memory, called in the end of each battle
void emptyCardSet(cardList **cardSet)
{
    while((*cardSet)->nextCard != NULL)
        removeCard(cardSet, 1);
    
    printf("freeing root\n");
    free((*cardSet));
}

// Game saving?
void savecardSetFile(cardList **cardSet)
{
    // TODO: open file and save card data in local storage
}

// Game loading?
void loadcardSetFile(cardList **cardSet)
{
    // TODO: open a local data storage (if present) and load card data
}

void formEnemyDeck(cardList **cardSet)
{
    //TODO: random enemy cardSet generation
}

// Should be used for enemy only??
// Also testing purposes
void makeRandomCard(cardList **cardSet)
{
    int maxHp = rand() % 3 + 1;
    int curHp = maxHp;
    
    int random = rand() % 3 + 1;

    char *cardPath = "../Textures/Ghoul_";
    int dmgType = 0;

    switch (random)
    {
        case 1:
            strcat(cardPath, "1.png");
            dmgType = 2;
            break;

        case 2:
            strcat(cardPath, "2.png");
            dmgType = 1;
            break;

        case 3:
            strcat(cardPath, "3.png");
            dmgType = 0;
            break;

        default:
            printf("[ERROR] Unknown random parameters\n");
    }
    
    addCard(cardSet, cardPath, dmgType, curHp, maxHp, "Ghoul");
}