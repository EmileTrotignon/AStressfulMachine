//
// Created by emile on 14/03/19.
//

#ifndef A_STRESSFUL_MACHINE_NCURSES_H
#define A_STRESSFUL_MACHINE_NCURSES_H

#include <ncurses.h>

#include "NcursesWindow.h"
#include "NcursesMenu.h"
#include "NcursesTypingField.h"

namespace ncursespp
{
    extern NcursesWindow *stdscr_;

    void initscr_();

    void endwin_();
}
#endif //A_STRESSFUL_MACHINE_NCURSES_H
