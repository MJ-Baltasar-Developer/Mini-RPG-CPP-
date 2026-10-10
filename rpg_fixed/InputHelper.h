#ifndef INPUT_HELPER_H
#define INPUT_HELPER_H

#include <iostream>
#include <limits>
#include <cstdlib>

using namespace std;

inline int getValidInt(int min, int max)
{
    int value;
    while (!(cin >> value) || value < min || value > max)
    {
        if (cin.eof()) exit(0);   // input stream closed: quit instead of looping forever
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter a number between " << min << " and " << max << ": ";
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return value;
}

#endif // INPUT_HELPER_H