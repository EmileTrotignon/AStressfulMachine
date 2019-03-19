//
// Created by emile on 10/03/19.
//
#include <iostream>
#include <vector>
#include <string>
#include <ncurses.h>
#include <assert.h>

#include "ncurses++.h"

bool test_OCursedStream()
{
    using namespace ncursespp;
    initscr_();
    noecho();
    Window lol = Window(stdscr_->get_height(), stdscr_->get_width(), 0, 0);
    OCursedStream lols = OCursedStream(&lol, 3, 3);
    lols << "qwertyuiop";
    lols << 'a';
    lols.flush();
    lol.getch_();
    endwin_();
    return true;
}

int main()
{
    assert(test_OCursedStream());
    cout << "tests passed" << endl;
    return 0;
}