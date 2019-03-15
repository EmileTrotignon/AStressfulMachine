//
// Created by emile on 14/03/19.
//

#include "NcursesWindow.h"

namespace ncursespp
{
    NcursesWindow::NcursesWindow() : height(0), width(0), starty(0), startx(0), boxing(false), window(nullptr)
    {
    }

    NcursesWindow::NcursesWindow(int height_, int width_, int starty_, int startx_, bool boxing_) :
            height(height_),
            width(width_),
            starty(starty_),
            startx(startx_),
            boxing(boxing_)
    {
        window = newwin(height, width, starty, startx);
        refresh();
    }

    NcursesWindow::NcursesWindow(WINDOW *window_) : window(window_)
    {
        getmaxyx(window, height, width);
        boxing = false;
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

    void NcursesWindow::printstr_centered(int y, const string &s)
    {
        mvprintstr(y, (int) ((width / 2) - (s.size() / 2)), s);
    }

    void NcursesWindow::printstr_in_middle(const string &s)
    {
        mvprintstr(height / 2, (int) ((width / 2) - (s.size() / 2)), s);
    }

    void NcursesWindow::printw(const char *s, ...)
    {
        va_list args;
        va_start(args, s);
        wprintw(window, s, args);
    }

    void NcursesWindow::mvprintstr(int y, int x, string str, int border_size_x)
    {
        istringstream strs(str);
        string buff;
        if (boxing)
        {
            border_size_x++;
        }
        while (!strs.eof())
        {
            getline(strs, buff);
            for (int x_on_screen = x, x_in_str = 0; x_in_str < buff.size(); x_in_str++)
            {

                if (x_on_screen == (get_width() - border_size_x))
                {
                    x_on_screen = x;
                    y++;
                }
                mvaddch_(y, x_on_screen, (chtype) buff[x_in_str]);
                x_on_screen++;
            }
            buff = "";
            y++;
        }
    }

    void NcursesWindow::printstr(const string &str)
    {
        wprintw(window, str.c_str());
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

    int NcursesWindow::get_height() const
    {
        return height;
    }

    int NcursesWindow::get_width() const
    {
        return width;
    }

    int NcursesWindow::get_starty() const
    {
        return starty;
    }

    int NcursesWindow::get_startx() const
    {
        return startx;
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
            printstr(to_string(*i));
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
}
