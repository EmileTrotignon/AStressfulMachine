//
// Created by emile on 14/03/19.
//

#include "ncurses++.h"

namespace ncursespp
{
    Window *stdscr_ = nullptr;

    void initscr_()
    {
        initscr();
        stdscr_ = new Window(stdscr);
    }

    void endwin_()
    {
        delete stdscr_;
        endwin();
    }
}