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

void NcursesWindow::mvaddch_(int y, int x, const chtype ch)
{
    mvwaddch(window, y, x, ch);
}

void NcursesWindow::sbox()
{
    box(window, ACS_VLINE, ACS_HLINE);
}

int NcursesWindow::getch_()
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

void NcursesWindow::attron_(int attr)
{
    wattron(window, attr);
}


void NcursesWindow::attroff_(int attr)
{
    wattroff(window, attr);
}

void NcursesWindow::print_program_to_win(VirtualMachine *vm)
{
    const string &program = vm->get_program();

    for (auto i = program.begin(); i < program.end(); i++)
    {
        if (i == vm->get_current_operator())
        {
            color_on(1);
        }
        mvaddch_(height / 2, (int) (2 + i - program.begin()), (const chtype) *i);
        if (i == vm->get_current_operator())
        {
            color_off(1);
        }
    }
    refresh();
}

void NcursesWindow::print_memory_to_win(VirtualMachine *vm)
{
    const vector<int> &memory = vm->get_memory();
    move_cursor(get_height() / 2, 2);
    for (auto i = memory.begin(); i < memory.end(); i++)
    {
        if (i - memory.begin() == vm->get_memory_ptr() - vm->get_memory().begin()) color_on(1);
        printw("%d", *i);
        if (i - memory.begin() == vm->get_memory_ptr() - vm->get_memory().begin()) color_off(1);
        printw(" ");
    }
    refresh();
}


void NcursesWindow::print_input_to_win(GameLevel *gl)
{
    clear();
    mvprintstr(2, 2, gl->get_input_as_string());
    refresh();
}

