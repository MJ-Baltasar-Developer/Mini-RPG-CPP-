#include "Map.h"
#include "InputHelper.h"
#include <iostream>
#include "Random.h"

using namespace std;

Map::Map()
{
    mPlayerXPos = 0;
    mPlayerYPos = 0;
}

int  Map::getPlayerXPos() { return mPlayerXPos; }
int  Map::getPlayerYPos() { return mPlayerYPos; }

void Map::movePlayer()
{
    cout << "[1] North || [2] East || [3] South || [4] West: ";
    int selection = getValidInt(1, 4);

    switch(selection)
    {
    case 1: mPlayerYPos++; break;
    case 2: mPlayerXPos++; break;
    case 3: mPlayerYPos--; break;
    case 4: mPlayerXPos--; break;
    }
    cout << endl;
}

Monster* Map::checkRandomEncounter()
{
    int roll = Random(0, 20);
    if (roll <= 10) return nullptr;

    cout << "You encountered an Orc!" << endl;
    return new Monster("Orc", 10, 8, 200, 5, 1, "Short Sword", 2, 7);
}

void Map::printPlayerPos()
{
    cout << "Player Position = (" << mPlayerXPos << ", " << mPlayerYPos << ")"
         << "   [Merlin's Surplus is at (2, 4)]" << endl << endl;
}

void Map::shopEncounter(Player& player, Store& store)
{
    if (mPlayerXPos == 2 && mPlayerYPos == 4)
    {
        player.storeShopping(store);
    }
}