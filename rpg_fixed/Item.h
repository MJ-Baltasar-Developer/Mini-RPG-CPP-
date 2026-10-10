#ifndef ITEM_H
#define ITEM_H

#include <string>

using namespace std;

class Player;
class Monster;

class Item
{
public:
    Item(string name, int value) : mName(name), mItemValue(value) {}
    virtual ~Item() {}

    virtual bool use(Player& player, Monster* monster = nullptr) = 0;
    virtual Item* clone() const = 0;   // copy of the real (derived) object

    string getName() const { return mName; }
    int getValue() const { return mItemValue; }

protected:
    string mName;
    int    mItemValue;
};

class PotionItem : public Item
{
public:
    PotionItem(string name, int value, int healAmount)
        : Item(name, value), mHealAmount(healAmount) {}

    bool use(Player& player, Monster* monster = nullptr) override;
    Item* clone() const override { return new PotionItem(*this); }

private:
    int mHealAmount;
};

class AttackItem : public Item
{
public:
    AttackItem(string name, int value, int damage)
        : Item(name, value), mDamage(damage) {}

    bool use(Player& player, Monster* monster = nullptr) override;
    Item* clone() const override { return new AttackItem(*this); }

private:
    int mDamage;
};

#endif // ITEM_H