//
// Created by emile on 14/03/19.
//

#ifndef A_STRESSFUL_MACHINE_NCURSESWINDOW_H
#define A_STRESSFUL_MACHINE_NCURSESWINDOW_H

#include <ncurses.h>
#include "ncurses_utilities.h"

class NcursesWindow
{

private:

    int height;
    int width;
    int startx;
    int starty;
    bool boxing;
    WINDOW *window;

public:

    NcursesWindow(int height, int width, int startx, int starty, bool boxing = false);

    ~NcursesWindow();

    void mvprintw(int y, int x, const char *s, ...);

    void printw(const char *s, ...);

    void mvprintstr(int y, int x, string str);

    int get_ch();

    void sbox();

    void refresh();

    void move_cursor(int y, int x);

    void keypad_on();

    void clear_from_cursor_to_eol();

    void clear();

    int get_width();

    int get_height();

    void color_on(int color_id);

    void color_off(int color_id);

    void toggle_attr(int attr);

    void toggle_attr_off(int attr);
};


#endif //A_STRESSFUL_MACHINE_NCURSESWINDOW_H
