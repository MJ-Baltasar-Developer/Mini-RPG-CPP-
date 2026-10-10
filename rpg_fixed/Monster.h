#ifndef MONSTER_H
#define MONSTER_H

#include "Weapon.h"
#include <string>

using namespace std;

class Player;

class Monster
{
public:
    Monster(const string& name, int hp, int acc,
        int xpReward, int coinsReward, int armor, const string& weaponName,
        int lowDamage, int highDamage);

    bool isDead();

    int    getXPReward();
    int    getCoinsReward();
    string getName();
    int    getArmor();

    void attack(Player& player);
    void takeDamage(int damage);
    void displayHitPoints();

private:
    string mName;
    int    mHitPoints;
    int    mAccuracy;
    int    mExpReward;
    int    mGoldReward;
    int    mArmor;
    Weapon mWeapon;
};

#endif // MONSTER_H