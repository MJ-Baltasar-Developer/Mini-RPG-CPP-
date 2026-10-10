#ifndef MAP_H
#define MAP_H

#include "Player.h"
#include "Monster.h"
#include "Store.h"

using namespace std;

class Map
{
public:
    Map();

    int  getPlayerXPos();
    int  getPlayerYPos();
    void movePlayer();
    Monster* checkRandomEncounter();
    void printPlayerPos();
    void shopEncounter(Player& player, Store& store);

private:
    int mPlayerXPos;
    int mPlayerYPos;
};

#endif // MAP_H