//
// Created by emile on 05/03/19.
//

#ifndef A_STRESSFUL_MACHINE_GAMESEQUENCE_H
#define A_STRESSFUL_MACHINE_GAMESEQUENCE_H

#include "GameLevel.h"

/**
 * This class is used to represent a game of A Stressful Virtual Machine once the player choose a save file.
 */
class GameSequence
{
private:

    map<string, GameLevel *> available_levels;

    GameLevel current_level;

    void load_from_save();

public:
    GameSequence(const string &savename, const string &gamefiles_dir);

    void select_level(const string &level);


};


#endif //A_STRESSFUL_MACHINE_GAMESEQUENCE_H
