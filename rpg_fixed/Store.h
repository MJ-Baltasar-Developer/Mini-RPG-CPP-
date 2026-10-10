#ifndef STORE_H
#define STORE_H

#include "Weapon.h"
#include "Armor.h"
#include "Item.h"
#include <string>

using namespace std;

class Player;

class Store
{
public:
    Store();
    ~Store();

    int  enterStore();
    void showItems();
    int  chooseItem();

    Item*  getCatalogItem(int index);
    Weapon getWeapon() const { return mWeapon; }
    Armor  getArmor() const { return mArmor; }

private:
    Item*  mCatalog[2];
    Weapon mWeapon;
    Armor  mArmor;
};

#endif // STORE_H