//
// Created by emile on 06/03/19.
//

#ifndef A_STRESSFUL_MACHINE_GAME_H
#define A_STRESSFUL_MACHINE_GAME_H

#include "SavePicker.h"

namespace fs = filesystem;

class Game
{
protected:

    SavePicker *save_picker;
    GameSequence *game_sequence;
    fs::path gamefiles_dir;


public:

    /**
     * SavePicker
     * @param save_dir
     * @param gamefiles_dir_
     */
    Game(const fs::path &save_dir, fs::path gamefiles_dir_);

    virtual void play() = 0;

};


#endif //A_STRESSFUL_MACHINE_GAME_H
