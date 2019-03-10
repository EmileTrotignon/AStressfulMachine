//
// Created by emile on 06/03/19.
//

#ifndef A_STRESSFUL_MACHINE_GAMETUI_H
#define A_STRESSFUL_MACHINE_GAMETUI_H

#include <ncurses.h>
#include <menu.h>

#include "Game.h"

class GameTUI : public Game
{
private:

    void pick_saves();

    void pick_level();

public:
    GameTUI(const string &saves_dir, const string &gamefiles_dir);

    void play() override;

};


#endif //A_STRESSFUL_MACHINE_GAMETUI_H
