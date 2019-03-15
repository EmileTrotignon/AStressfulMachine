//
// Created by emile on 14/03/19.
//

#include "ncurses++.h"

namespace ncursespp
{
    NcursesWindow *stdscr_ = nullptr;

    void initscr_()
    {
        initscr();
        stdscr_ = new NcursesWindow(stdscr);
    }

    void endwin_()
    {
        delete stdscr_;
        endwin();
    }
}