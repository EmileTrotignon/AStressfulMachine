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

    fs::path saves_dir;
    string savename;
    vector<string> available_levels;
    map<string, GameLevel *> levels;
    GameLevel *current_level;
    string gamefiles_dir;

    vector<bool> attempted;
    vector<bool> succeeded_levels;
    vector<vector<float>> average_speed;
    vector<vector<float>> average_memory_use;

    void load_from_save();

    void conform_save_to_gamefiles();
    
    void save_to_xml();

    void load_from_xml();

public:
    GameSequence(string savename, fs::path saves_dir, const fs::path &gamefiles_dir);

    void select_level(const string &level_name);

    vector<string> get_available_levels() const;

    GameLevel *get_current_level();

    void save_to_save();

};


#endif //A_STRESSFUL_MACHINE_GAMESEQUENCE_H
