#include "Map.h"
#include "Player.h"
#include "Random.h"
#include "Store.h"
#include "InputHelper.h"

#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

static void combat(bool &done, Player &mainPlayer, Monster *&monster) {
    while (true)
    {
        mainPlayer.displayHitandMagicPoints();
        monster->displayHitPoints();
        cout << endl;
        
        bool runAway = mainPlayer.attack(*monster);
        
        if (runAway)
            break;
        
        if (monster->isDead())
        {
            mainPlayer.victory(monster->getXPReward(), monster->getCoinsReward());
            mainPlayer.levelUp();
            break;
        }
        
        monster->attack(mainPlayer);
        
        if (mainPlayer.isDead())
        {
            mainPlayer.gameover();
            done = true;
            break;
        }
    }
    
    delete monster;
    monster = nullptr;
}

int main()
{
    srand(static_cast<unsigned int>(time(0)));

    Map gameMap;
    Store store;
    Player mainPlayer;

    mainPlayer.createClass();
    mainPlayer.createRace();

    bool done = false;
    while (!done)
    {
        gameMap.printPlayerPos();
        cout << "[1] Move || [2] Rest || [3] Inventory || [4] View Stats || [5] Quit: ";
        
        int selection = getValidInt(1, 5);
        Monster* monster = nullptr;

        switch (selection)
        {
        case 1:
            gameMap.movePlayer();
            gameMap.shopEncounter(mainPlayer, store);
            monster = gameMap.checkRandomEncounter();
            if (monster != nullptr) combat(done, mainPlayer, monster);
            break;

        case 2:
            // 1-in-4 chance of being ambushed while resting
            if (Random(1, 4) == 1)
                monster = gameMap.checkRandomEncounter();

            if (monster != nullptr) combat(done, mainPlayer, monster);
            else mainPlayer.rest();
            break;

        case 3:
            mainPlayer.useItem(nullptr);
            break;

        case 4:
            mainPlayer.viewStats();
            break;

        case 5:
            done = true;
            break;
        }
    }

    return 0;
}