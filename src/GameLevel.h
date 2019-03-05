//
// Created by emile on 04/03/19.
//

#ifndef LIFAP4_PROJECT_GAMELEVEL_H
#define LIFAP4_PROJECT_GAMELEVEL_H

#include <fstream>
#include "VirtualMachine.h"
#include "utilities.h"

#define LEVELFILES_FOLDER "data/gamefiles/levels"

class GameLevel
{
private:
    string level_name;
    string solution;
    string instructions;
    ifstream input;
    bool attempt(const string & program, int verbose_level = 0);
    void play_sequence();
public:
    GameLevel(const string &level_name);
    void play();
};


#endif //LIFAP4_PROJECT_GAMELEVEL_H
