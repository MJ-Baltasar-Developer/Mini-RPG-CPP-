#ifndef SPELL_H
#define SPELL_H

#include <string>
#include "Range.h"

struct Spell
{
    std::string mName                = "Default Spell";
    Range       mDamageRange         = {0, 0};
    int         mMagicPointsRequired = 0;
};

#endif // SPELL_H
