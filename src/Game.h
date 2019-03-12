//
// Created by emile on 06/03/19.
//

#ifndef A_STRESSFUL_MACHINE_GAME_H
#define A_STRESSFUL_MACHINE_GAME_H

#include "SavePicker.h"

class Game
{
protected:

    SavePicker *save_picker;
    GameSequence *game_sequence;
    string gamefiles_dir;

public:

    /**
     * SavePicker
     * @param save_dir
     * @param gamefiles_dir
     */
    Game(const string &save_dir, const string &gamefiles_dir);

    virtual void play() = 0;

};


#endif //A_STRESSFUL_MACHINE_GAME_H
