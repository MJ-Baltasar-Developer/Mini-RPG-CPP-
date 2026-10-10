#include <iostream>
#include "Store.h"
#include "InputHelper.h"

using namespace std;

Store::Store()
{
    mCatalog[0] = new PotionItem("Jungle Juice", 3, 10);
    mCatalog[1] = new AttackItem("Magic Fireball", 10, 15);

    mWeapon.mName = "Bahamut's Soul";
    mWeapon.mWeaponValue = 8;
    mWeapon.mWeaponDamage = 8;
    mWeapon.mDamageRange = {4, 8};   // what combat actually uses

    mArmor.mName = "Iron Clad";
    mArmor.mArmorValue = 5;
    mArmor.mArmorEffect = 3;
}

Store::~Store()
{
    delete mCatalog[0];
    delete mCatalog[1];
}

int Store::enterStore()
{
    cout << "============= Welcome to Merlin's Surplus! =============" << endl;
    cout << "================ [1] Buy || [2] Sell || [3] Exit ========" << endl;
    cout << "Choice: ";
    return getValidInt(1, 3);
}

void Store::showItems()
{
    cout << "\n============= Items for Sale =============" << endl;
    cout << "[1] " << mCatalog[0]->getName() << " (Potion)   Costs: [" << mCatalog[0]->getValue() << "]" << endl;
    cout << "[2] " << mCatalog[1]->getName() << " (Attack)   Costs: [" << mCatalog[1]->getValue() << "]" << endl;
    cout << "[3] " << mWeapon.mName          << " (Weapon)   Costs: [" << mWeapon.mWeaponValue   << "]" << endl;
    cout << "[4] " << mArmor.mName           << " (Armor)    Costs: [" << mArmor.mArmorValue    << "]" << endl;
    cout << "[5] Leave Store" << endl;
    cout << "==========================================" << endl;
}

int Store::chooseItem()
{
    cout << "Purchase choice [1-5]: ";
    return getValidInt(1, 5);
}

Item* Store::getCatalogItem(int index)
{
    if (index >= 0 && index < 2) return mCatalog[index];
    return nullptr;
}