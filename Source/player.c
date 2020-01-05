#include "player.h"

void initPlayer(PlayerCaravan *player)
{
    initCardSet(&player->deckList);
    player->wagon.goods = createList();
}

int getPlayerCards(cardList **deckList)
{
    int totalCards = 0;
    addCard(deckList, "../Textures/Archer_1.png", AGILITY, 3, 3, 1, "Alfredo");
    addCard(deckList, "../Textures/Soldier_1.png", STRENGTH, 6, 6, 2, "Ivan");
    addCard(deckList, "../Textures/Spearman_1.png", CHARISMA, 4, 4, 3, "Xin Yang");
    totalCards += 3; // TODO: make this random

    return totalCards;
}
