#include "cards.h"

// TODO: should be consequatively called from load cards to fill deck
void addCard(cardList **cardSet, char *pathTexture, int dmgType, int curHp, int maxHp, int id, char *name)
{
    cardList *tmp;
    cardList *last = getLast(cardSet);    

    tmp = (cardList *)malloc(sizeof(cardList));

    if (tmp)
    {
        tmp->card.cardTexture = LoadTexture(pathTexture);
        tmp->card.number = id;
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
    
    if (del_tmp != NULL)
    {
        cardList *save = del_tmp->nextCard->nextCard;

        UnloadTexture(del_tmp->nextCard->card.cardTexture);
        free(del_tmp->nextCard->card.name);
        free(del_tmp->nextCard);

        del_tmp->nextCard = save;

        // Decreasing all id's after certain element was deleted for random picks to work correctly
        // Kind of lame, so may be TODO later..
        del_tmp = del_tmp->nextCard;
        while (del_tmp != NULL)
        {
            del_tmp->card.number--;
            del_tmp = del_tmp->nextCard;
        }
    }
    else
        printf("Deleting unknown element?\n"); // Still no error detection...
}

// Called in case card dies and has to be removed from deck (^^^^)
cardList* getCard(cardList **cardSet, int number)
{
    cardList *tmp = (*cardSet);

    while (tmp->nextCard->card.number != number)
    {
        if (tmp == NULL)
            return NULL;

        tmp = tmp->nextCard;
    }
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
        removeCard(cardSet, (*cardSet)->nextCard->card.number);
    
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

// Should be used for enemy only??
// Also testing purposes
void makeRandomCard(cardList **cardSet)
{
    static int id = 1;
    int maxHp = rand() % 10 + 1;
    int curHp = maxHp;
    
    int random = rand() % 3 + 1;

    char cardPath[50] = "../Textures/Ghoul_";
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

    printf("ready\n");
    addCard(cardSet, cardPath, dmgType, curHp, maxHp, id, "Ghoul");
    id++;

    //Hardcode, but id has to be limited to max amount of cards in set or crashes
    if (id > 3)
        id = 1;
}

void initEnemyRandomDeck(cardList **enemyCardSet, int amount)
{
    for (int i = 0; i < amount; i++)
        makeRandomCard(enemyCardSet);

    cardList *tmp = (*enemyCardSet)->nextCard;

    // We don;t know enemy stats by default
    // They are being revealed after fight
    while (tmp != NULL)
    {
        tmp->card.isVisible = FALSE;
        tmp = tmp->nextCard;
    }
}