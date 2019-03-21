//
// Created by emile on 14/03/19.
//

#ifndef A_STRESSFUL_MACHINE_NCURSES_H
#define A_STRESSFUL_MACHINE_NCURSES_H

#include <ncurses.h>

#include "Window.h"
#include "Menu.h"
#include "Field.h"
#include "OCursedStream.h"
#include "MessageStack.h"

namespace ncursespp
{
    extern Window *stdscr_;

    void initscr_();

    void endwin_();

    void get_specific_ch(int c);
}
#endif //A_STRESSFUL_MACHINE_NCURSES_H
