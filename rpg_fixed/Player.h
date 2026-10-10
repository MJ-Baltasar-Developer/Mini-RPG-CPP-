#ifndef PLAYER_H
#define PLAYER_H

#include "Weapon.h"
#include "Armor.h"
#include "Spell.h"
#include "Monster.h"
#include "Item.h"
#include "Store.h"
#include <string>

using namespace std;

class Player
{
public:
    Player();
    ~Player();

    bool isDead();
    int  getArmor();
    void takeDamage(int damage);
    void heal(int amount);

    string getSpell();
    int  getSpellDamage(Monster& monster, string spellName);

    void createClass();
    void createRace();
    bool attack(Monster& monster);
    void levelUp();
    void rest();
    void viewStats();
    void victory(int xp, int coins);
    void gameover();
    void displayHitandMagicPoints();

    // Inventory & Store Methods
    void storeShopping(Store& store);
    void buying(Store& store);
    void selling(Store& store);
    bool useItem(Monster* monster = nullptr);

private:
    string mName;
    string mClassName;
    string mRaceName;
    int    mAccuracy;
    int    mHitPoints;
    int    mMaxHitPoints;
    int    mMagicPoints;
    int    mMaxMagicPoints;
    int    mExpPoints;
    int    mNextLevelExp;
    int    mLevel;
    int    mArmor;
    int    mGold;
    Weapon mWeapon;
    Spell  mSpell;
    Spell  mSpell2;
    Item*  mInventory[2];
};

#endif // PLAYER_H