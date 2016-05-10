/******************************************************************************************
 * Project: Predator and Prey
 * Author: Ke Wei
 * Class: CS3A
 * Due date: April 13, 2016
 * Prjection discpriton: simulate a predator and prey interaction in the ecosystem
 * Last Date Modified: April 13, 2016
 *******************************************************************************************/

#include <cstdlib>
#include <time.h>
#include <iostream>
#include "game.h"
using namespace std;

int main()
{
    srand(time(NULL));
    cout << "=========Start==========" << endl;
    Game game;
    game.Run();
    cout << "=========End=========="<<endl;
    return 0;
}

