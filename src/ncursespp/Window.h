//
// Created by emile on 14/03/19.
//

#ifndef A_STRESSFUL_MACHINE_NCURSESWINDOW_H
#define A_STRESSFUL_MACHINE_NCURSESWINDOW_H

#include <iostream>
#include <vector>
#include <ncurses.h>

using namespace std;

namespace ncursespp
{
    class Window
    {

    protected:

        int height;
        int width;
        int startx;
        int starty;
        bool boxing;
        WINDOW *window;

    public:


        Window();

        Window(int height, int width, int starty, int startx, bool boxing = false);

        Window(Window *masterwin, int height, int width, int starty, int startx, bool boxing = false);

        explicit Window(WINDOW *window);

        ~Window();

        void mvprintw(int y, int x, const char *s, ...);

        void printw(const char *s, ...);

        void mvprint_line(int y, int x, const string &str);

        void mvprint_multiline_str(int y, int x, string str, int x_padding = 0);

        void printstr(const string &str);

        void printstr_centered(int y, const string &s);

        void printstr_in_middle(const string &s);

        void mvaddch_(int y, int x, chtype ch);

        int getch_();

        void get_specific_ch(int c);

        int getch_(const vector<int> &s);

        int nodelay_getch();

        void sbox();

        virtual void refresh_();

        void move_cursor(int y, int x);

        void keypad_on();

        void clear_from_cursor_to_eol();

        void erase();

        void clear();

        int get_width() const;

        int get_height() const;

        int get_starty() const;

        int get_startx() const;

        int get_x() const;

        int get_y() const;

        void color_on(int color_id);

        void color_off(int color_id);

        void attron_(int attr);

        void attroff_(int attr);

    };
}

#endif //A_STRESSFUL_MACHINE_NCURSESWINDOW_H
