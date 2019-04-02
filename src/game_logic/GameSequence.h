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

    friend class GameLevel; // Pour pouvoir acceder à
private:

    string savename;
    vector<string> available_levels;
    vector<GameLevel *> levels;
    vector<GameLevel *>::iterator current_level;
    string gamefiles_dir;

    vector<bool> attempted;
    vector<bool> succeeded_levels;
    vector<vector<float>> average_speed;
    vector<vector<float>> average_memory_use;

    void load_from_save();

    void conform_save_to_gamefiles();
    
    void save_to_xml();

    void load_to_xml();

public:
    GameSequence(const string &savename, const string &gamefiles_dir);

    void select_level(int level_index);

    vector<string> get_available_levels() const;

    vector<GameLevel *>::iterator get_current_level();

    void save_to_save();

};


#endif //A_STRESSFUL_MACHINE_GAMESEQUENCE_H
