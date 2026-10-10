#ifndef RANDOM_H
#define RANDOM_H

#include <cstdlib>
#include <utility>
#include "Range.h"

// Random integer in [low, high], inclusive. Call srand() once in main().
inline int Random(int low, int high)
{
    if (high < low) std::swap(low, high);
    return low + std::rand() % (high - low + 1);
}

// Random integer within a Range (inclusive).
inline int Random(const Range& range)
{
    return Random(range.mLow, range.mHigh);
}

#endif // RANDOM_H
