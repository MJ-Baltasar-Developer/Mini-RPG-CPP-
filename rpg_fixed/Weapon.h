#ifndef WEAPON_H
#define WEAPON_H

#include <string>
#include "Range.h"

// Used by Player (equipped weapon), Monster (its attack), and Store (item for sale).
struct Weapon
{
    std::string mName         = "Default Weapon";
    Range       mDamageRange  = {0, 0};   // what combat actually rolls against
    int         mWeaponValue  = 0;        // gold cost in the Store
    int         mWeaponDamage = 0;        // Store display value (not used in combat)
};

#endif // WEAPON_H
