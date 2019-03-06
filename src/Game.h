//
// Created by emile on 06/03/19.
//

#ifndef A_STRESSFUL_MACHINE_GAME_H
#define A_STRESSFUL_MACHINE_GAME_H

#include "SavePicker.h"

class Game
{
private:

    SavePicker *save_picker;
    GameSequence *game_sequence;

public:

    Game(const string &save_dir, const string &gamefiles_dir);

    virtual play();

    virtual display();

};


#endif //A_STRESSFUL_MACHINE_GAME_H
