#include "Item.h"
#include "Player.h"
#include "Monster.h"
#include <iostream>

using namespace std;

bool PotionItem::use(Player& player, Monster* monster)
{
    player.heal(mHealAmount);
    cout << "You used " << mName << " and restored " << mHealAmount << " HP!" << endl;
    return true;
}

bool AttackItem::use(Player& player, Monster* monster)
{
    if (monster == nullptr)
    {
        cout << "You can only cast " << mName << " during combat!" << endl;
        return false;
    }

    cout << "You cast " << mName << " dealing " << mDamage << " damage to " << monster->getName() << "!" << endl;
    monster->takeDamage(mDamage);
    return true;
}