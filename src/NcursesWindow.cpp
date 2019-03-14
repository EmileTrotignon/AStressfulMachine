//
// Created by emile on 14/03/19.
//

#include "NcursesWindow.h"


NcursesWindow::NcursesWindow(int height_, int width_, int startx_, int starty_, bool boxing_) : height(height_),
                                                                                                width(width_),
                                                                                                startx(startx_),
                                                                                                starty(starty_),
                                                                                                boxing(boxing_)
{
    window = newwin(height, width, starty, startx);
    refresh();
}

NcursesWindow::~NcursesWindow()
{
    werase(window);
    wrefresh(window);
    delwin(window);
}

void NcursesWindow::mvprintw(int y, int x, const char *s, ...)
{
    va_list args;
    va_start(args, s);
    mvwprintw(window, y, x, s, args);
}

void NcursesWindow::printw(const char *s, ...)
{
    va_list args;
    va_start(args, s);
    wprintw(window, s, args);
}

void NcursesWindow::mvprintstr(int y, int x, string str)
{
    istringstream strs(str);
    string buff;
    while (!strs.eof())
    {
        getline(strs, buff);
        mvwprintw(window, y, x, buff.c_str());
        buff = "";
        y++;
    }
}

void NcursesWindow::sbox()
{
    box(window, ACS_VLINE, ACS_HLINE);
}

int NcursesWindow::get_ch()
{
    return wgetch(window);
}

void NcursesWindow::refresh()
{
    if (boxing) sbox();
    wrefresh(window);
}

void NcursesWindow::move_cursor(int y, int x)
{
    wmove(window, y, x);
}

void NcursesWindow::keypad_on()
{
    keypad(window, TRUE);
}

void NcursesWindow::clear_from_cursor_to_eol()
{
    wclrtoeol(window);
}

void NcursesWindow::clear()
{
    wclear(window);

}

int NcursesWindow::get_height()
{
    return height;
}

int NcursesWindow::get_width()
{
    return width;
}

void NcursesWindow::color_on(int color_id)
{
    wattron(window, COLOR_PAIR(color_id));
}


void NcursesWindow::color_off(int color_id)
{
    wattroff(window, COLOR_PAIR(color_id));
}

void NcursesWindow::toggle_attr(int attr)
{
    wattron(window, attr);
}


void NcursesWindow::toggle_attr_off(int attr)
{
    wattroff(window, attr);
}