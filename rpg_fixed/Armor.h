#ifndef ARMOR_H
#define ARMOR_H

#include <string>

struct Armor
{
    std::string mName        = "Default Armor";
    int         mArmorValue  = 0;   // gold cost in the Store
    int         mArmorEffect = 0;   // armor rating added when bought
};

#endif // ARMOR_H
