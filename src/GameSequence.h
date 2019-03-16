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

    vector<string> available_levels;
    GameLevel *current_level;
    string gamefiles_dir;

    vector<bool> attempted;
    vector<bool> succeeded_levels;
    vector<vector<string>> attempts;
    vector<vector<float>> average_speed;
    vector<vector<float>> average_memory_use;

    void load_from_save();

public:

    GameSequence(const string &savename, const string &gamefiles_dir);

    void select_level(const string &level);

    vector<string> get_available_levels() const;

    GameLevel *get_current_level();


};


#endif //A_STRESSFUL_MACHINE_GAMESEQUENCE_H
