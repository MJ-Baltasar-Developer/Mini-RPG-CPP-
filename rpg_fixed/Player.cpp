#include <iostream>
#include <algorithm>
#include "Player.h"
#include "Random.h"
#include "Store.h"
#include "InputHelper.h"

using namespace std;

Player::Player()
{
    mName         = "Default";
    mClassName    = "Default";
    mRaceName     = "Default";
    mAccuracy     = 0;
    mHitPoints    = 0;
    mMaxHitPoints = 0;
    mMagicPoints  = 0;
    mMaxMagicPoints = 0;
    mExpPoints    = 0;
    mNextLevelExp = 1000;
    mLevel        = 1;
    mArmor        = 0;
    mGold         = 0;

    mWeapon.mName = "Default Weapon";
    mWeapon.mDamageRange = {0, 0};

    mSpell.mName = "Default Spell";
    mSpell.mDamageRange = {0, 0};
    mSpell.mMagicPointsRequired = 0;

    mSpell2.mName = "Default Spell 2";
    mSpell2.mDamageRange = {0, 0};
    mSpell2.mMagicPointsRequired = 0;

    mInventory[0] = nullptr;
    mInventory[1] = nullptr;
}

Player::~Player()
{
    delete mInventory[0];
    mInventory[0] = nullptr;
    delete mInventory[1];
    mInventory[1] = nullptr;
}

bool Player::isDead() { return mHitPoints <= 0; }
int  Player::getArmor() { return mArmor; }
void Player::takeDamage(int damage) { mHitPoints = max(0, mHitPoints - damage); }

void Player::heal(int amount)
{
    mHitPoints += amount;
    if (mHitPoints > mMaxHitPoints) mHitPoints = mMaxHitPoints;
}

string Player::getSpell()
{
    cout << "========== Spell Slot ==========" << endl;
    cout << "[1] " << mSpell.mName << " (MP: " << mSpell.mMagicPointsRequired << ")" << endl;
    cout << "[2] " << mSpell2.mName << " (MP: " << mSpell2.mMagicPointsRequired << ")" << endl;
    cout << "Choice [1-2]: ";
    
    int selection = getValidInt(1, 2);
    return (selection == 1) ? mSpell.mName : mSpell2.mName;
}

int Player::getSpellDamage(Monster& monster, string spellName)
{
    Range range = (spellName == mSpell.mName) ? mSpell.mDamageRange : mSpell2.mDamageRange;
    int damage = Random(range) - monster.getArmor();
    return max(0, damage);
}

void Player::createClass()
{
    cout << "CHARACTER CLASS GENERATION\n==========================" << endl;
    cout << "Enter your character's name: ";
    
    getline(cin, mName);   // getValidInt() already consumed the leftover newline
    if (mName.empty()) mName = "Hero";

    cout << "Please select a character class...\n[1] Fighter || [2] Wizard || [3] Cleric || [4] Thief: ";
    int characterNum = getValidInt(1, 4);

    switch (characterNum)
    {
    case 1:
        mClassName = "Fighter"; mAccuracy = 10; mHitPoints = mMaxHitPoints = 40;
        mMagicPoints = mMaxMagicPoints = 5; mArmor = 4; mGold = 5;
        mWeapon.mName = "Long Sword"; mWeapon.mDamageRange = {1, 8};
        mSpell = {"Spinning Strike", {3, 5}, 5};
        break;
    case 2:
        mClassName = "Wizard"; mAccuracy = 5; mHitPoints = mMaxHitPoints = 20;
        mMagicPoints = mMaxMagicPoints = 35; mArmor = 1; mGold = 5;
        mWeapon.mName = "Staff"; mWeapon.mDamageRange = {1, 4};
        mSpell = {"Eldritch Blast", {8, 15}, 15};
        break;
    case 3:
        mClassName = "Cleric"; mAccuracy = 8; mHitPoints = mMaxHitPoints = 30;
        mMagicPoints = mMaxMagicPoints = 15; mArmor = 3; mGold = 5;
        mWeapon.mName = "Flail"; mWeapon.mDamageRange = {1, 6};
        mSpell = {"Divine Shower", {6, 10}, 10};
        break;
    case 4:
    default:
        mClassName = "Thief"; mAccuracy = 7; mHitPoints = mMaxHitPoints = 24;
        mMagicPoints = mMaxMagicPoints = 10; mArmor = 2; mGold = 5;
        mWeapon.mName = "Short Sword"; mWeapon.mDamageRange = {1, 6};
        mSpell = {"Poltergeist", {10, 25}, 10};
        break;
    }
}

void Player::createRace()
{
    cout << "\nCHARACTER RACE GENERATION\n==========================" << endl;
    cout << "Select race [1] Dragonborn || [2] Demi-God || [3] Vampire || [4] Human: ";
    int characterNum = getValidInt(1, 4);

    switch (characterNum)
    {
    case 1:
        mRaceName = "Dragonborn"; mAccuracy -= 3; mArmor += 3; mGold = 0;
        mWeapon.mName = "Black Catcher"; mWeapon.mDamageRange.mHigh = 10;
        mSpell2 = {"Draco Meteor", {4, 20}, 5};
        break;
    case 2:
        mRaceName = "Demi-God"; mAccuracy -= 2; mHitPoints += 30; mMaxHitPoints += 30;
        mArmor = 0; mGold += 5;
        mWeapon.mName = "Will of the Gods"; mWeapon.mDamageRange.mHigh = 12;
        mSpell2 = {"Zeus' Wrath", {8, 15}, 10};
        break;
    case 3:
        mRaceName = "Vampire"; mAccuracy += 30; mHitPoints -= 5; mMaxHitPoints -= 5;
        mGold += 30; mWeapon.mName = "Bloodcradler"; mWeapon.mDamageRange.mLow = 3;
        mSpell2 = {"Carnage", {5, static_cast<int>(mGold * 0.25)}, 8};
        break;
    case 4:
    default:
        mRaceName = "Human"; mAccuracy += 10; mArmor = 0; mGold += 5;
        mWeapon.mName = "Excalibur"; mWeapon.mDamageRange.mLow = 2;
        mSpell2 = {"People Power", {5, static_cast<int>(mAccuracy * 0.5)}, 5};
        break;
    }
}

// Returns true if the player ran away. Invalid actions (not enough MP,
// empty item slot) re-prompt instead of wasting the turn.
bool Player::attack(Monster& monster)
{
    while (true)
    {
        cout << "[1] Attack || [2] Cast Spell || [3] Use Item || [4] Run: ";
        int selection = getValidInt(1, 4);

        switch (selection)
        {
        case 1:
        {
            cout << "You attack " << monster.getName() << " with " << mWeapon.mName << endl;
            if (Random(0, 20) < mAccuracy)
            {
                int totalDamage = Random(mWeapon.mDamageRange) - monster.getArmor();
                if (totalDamage <= 0) cout << "Your attack failed to penetrate armor." << endl;
                else
                {
                    cout << "You hit for " << totalDamage << " damage!" << endl;
                    monster.takeDamage(totalDamage);
                }
            }
            else cout << "You miss!" << endl;
            return false;
        }
        case 2:
        {
            string spellName = getSpell();
            int mpReq = (spellName == mSpell.mName) ? mSpell.mMagicPointsRequired : mSpell2.mMagicPointsRequired;

            if (mMagicPoints < mpReq)
            {
                cout << "Not enough Magic Points! Choose another action." << endl;
                break;   // back to the menu, turn not used
            }

            mMagicPoints -= mpReq;
            if (Random(0, 20) < mAccuracy)
            {
                int totalDamage = getSpellDamage(monster, spellName);
                cout << "Cast " << spellName << " dealing " << totalDamage << " damage!" << endl;
                monster.takeDamage(totalDamage);
            }
            else cout << "Your spell missed!" << endl;
            return false;
        }
        case 3:
            if (useItem(&monster)) return false;
            break;   // empty slot / nothing used: back to the menu
        case 4:
        default:
            if (Random(1, 4) == 1)
            {
                cout << "You safely ran away!" << endl;
                return true;
            }
            cout << "You could not escape!" << endl;
            return false;
        }
    }
}

bool Player::useItem(Monster* monster)
{
    cout << "========== Inventory ==========" << endl;
    cout << "[1] " << (mInventory[0] ? mInventory[0]->getName() : "Empty") << endl;
    cout << "[2] " << (mInventory[1] ? mInventory[1]->getName() : "Empty") << endl;
    cout << "Select item slot [1-2]: ";

    int slot = getValidInt(1, 2) - 1;

    if (mInventory[slot] == nullptr)
    {
        cout << "That inventory slot is empty!" << endl;
        return false;
    }

    if (mInventory[slot]->use(*this, monster))
    {
        delete mInventory[slot];
        mInventory[slot] = nullptr;
        return true;
    }

    return false;
}

void Player::buying(Store& store)
{
    int choice = 1;
    while (choice == 1)
    {
        int freeSlot = (mInventory[0] == nullptr) ? 0 : ((mInventory[1] == nullptr) ? 1 : -1);

        store.showItems();
        int selection = store.chooseItem();
        if (selection == 5) break;   // Leave Store

        if (selection == 1 || selection == 2)
        {
            if (freeSlot == -1) cout << "Your inventory is full!" << endl;
            else
            {
                Item* storeItem = store.getCatalogItem(selection - 1);
                if (storeItem && mGold >= storeItem->getValue())
                {
                    mGold -= storeItem->getValue();
                    mInventory[freeSlot] = storeItem->clone();

                    cout << "Purchased " << mInventory[freeSlot]->getName() << "!" << endl;
                }
                else cout << "Not enough gold!" << endl;
            }
        }
        else if (selection == 3)
        {
            Weapon w = store.getWeapon();
            if (mGold >= w.mWeaponValue)
            {
                mGold -= w.mWeaponValue;
                mWeapon = w;
                cout << "Equipped Weapon: " << mWeapon.mName << endl;
            }
            else cout << "Not enough gold!" << endl;
        }
        else if (selection == 4)
        {
            Armor a = store.getArmor();
            if (mGold >= a.mArmorValue)
            {
                mGold -= a.mArmorValue;
                mArmor += a.mArmorEffect;
                cout << "Equipped Armor! Rating boosted by " << a.mArmorEffect << endl;
            }
            else cout << "Not enough gold!" << endl;
        }

        cout << "\nCurrent Gold: " << mGold << "\nBuy another item? [1] Yes || [2] No: ";
        choice = getValidInt(1, 2);
    }
}

void Player::selling(Store& store)
{
    int choice = 1;
    while (choice == 1)
    {
        cout << "\n========== Sell Inventory ==========" << endl;
        cout << "[1] " << (mInventory[0] ? mInventory[0]->getName() : "Empty") << endl;
        cout << "[2] " << (mInventory[1] ? mInventory[1]->getName() : "Empty") << endl;
        cout << "Select slot to sell [1-2]: ";

        int slot = getValidInt(1, 2) - 1;
        if (mInventory[slot] != nullptr)
        {
            int sellPrice = mInventory[slot]->getValue() / 2;
            mGold += sellPrice;
            cout << "Sold " << mInventory[slot]->getName() << " for " << sellPrice << " gold!" << endl;
            delete mInventory[slot];
            mInventory[slot] = nullptr;
        }
        else cout << "That slot is already empty!" << endl;

        cout << "Current Gold: " << mGold << "\nSell another item? [1] Yes || [2] No: ";
        choice = getValidInt(1, 2);
    }
}

void Player::storeShopping(Store& store)
{
    int choice = store.enterStore();
    if (choice == 1) buying(store);
    else if (choice == 2) selling(store);
    cout << "Thank you for visiting Merlin's Surplus!\n" << endl;
}

void Player::levelUp()
{
    while (mExpPoints >= mNextLevelExp)
    {
        mLevel++;
        mNextLevelExp = mLevel * mLevel * 1000;
        mMaxHitPoints += 5;
        mMaxMagicPoints += 3;
        mHitPoints = mMaxHitPoints;
        mMagicPoints = mMaxMagicPoints;
        cout << "Level Up! You reached level " << mLevel << "!" << endl;
    }
}

void Player::rest()
{
    cout << "Resting... Health and Magic points fully restored!" << endl;
    mHitPoints = mMaxHitPoints;
    mMagicPoints = mMaxMagicPoints;
}

void Player::viewStats()
{
    cout << "PLAYER STATS\n============" << endl;
    cout << "Name: " << mName << " | Class: " << mClassName << " | Race: " << mRaceName << endl;
    cout << "HP: " << mHitPoints << "/" << mMaxHitPoints << " | MP: " << mMagicPoints << "/" << mMaxMagicPoints << endl;
    cout << "Armor: " << mArmor << " | Gold: " << mGold << " | Level: " << mLevel << " | XP: " << mExpPoints << endl;
    cout << "Weapon: " << mWeapon.mName << " (" << mWeapon.mDamageRange.mLow << "-" << mWeapon.mDamageRange.mHigh << " DMG)" << endl;
    cout << "Slot 1: " << (mInventory[0] ? mInventory[0]->getName() : "Empty") << endl;
    cout << "Slot 2: " << (mInventory[1] ? mInventory[1]->getName() : "Empty") << endl;
    cout << "==========================" << endl;
}

void Player::victory(int xp, int coins)
{
    cout << "Victory! Gained " << xp << " XP and " << coins << " Gold!" << endl;
    mExpPoints += xp;
    mGold += coins;
}

void Player::gameover()
{
    cout << "You died in battle...\nGAME OVER!\nPress '1' to continue: ";
    getValidInt(1, 9);
}

void Player::displayHitandMagicPoints()
{
    cout << mName << "'s HP = " << mHitPoints << ", MP = " << mMagicPoints << endl;
}