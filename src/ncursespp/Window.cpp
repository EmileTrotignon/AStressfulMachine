//
// Created by emile on 14/03/19.
//

#include <sstream>
#include <vector>
#include "Window.h"

namespace ncursespp
{
    Window::Window() : height(0), width(0), starty(0), startx(0), boxing(false), window(nullptr)
    {
    }

    Window::Window(int height_, int width_, int starty_, int startx_, bool boxing_) :
            height(height_),
            width(width_),
            starty(starty_),
            startx(startx_),
            boxing(boxing_)
    {
        window = newwin(height, width, starty, startx);
    }

    Window::Window(WINDOW *window_) : window(window_)
    {
        getmaxyx(window, height, width);
        boxing = false;
    }

    Window::Window(ncursespp::Window *masterwin, int height_, int width_, int starty_, int startx_, bool boxing_) :
            height(height_),
            width(width_),
            starty(starty_),
            startx(startx_),
            boxing(boxing_)
    {
        window = subwin(masterwin->window, height, width, starty + masterwin->get_starty(),
                        startx + masterwin->get_startx());
    }

    Window::~Window()
    {
        werase(window);
        wrefresh(window);
        delwin(window);
    }

    void Window::mvprintw(int y, int x, const char *s, ...)
    {
        va_list args;
        va_start(args, s);
        mvwprintw(window, y, x, s, args);
    }

    void Window::printstr_centered(int y, const string &s)
    {
        mvprintstr(y, (int) ((width / 2) - (s.size() / 2)), s);
    }

    void Window::printstr_in_middle(const string &s)
    {
        mvprintstr(height / 2, (int) ((width / 2) - (s.size() / 2)), s);
    }

    void Window::printw(const char *s, ...)
    {
        va_list args;
        va_start(args, s);
        wprintw(window, s, args);
    }

    void Window::mvprintstr(int y, int x, string str, int border_size_x)
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

    void Window::printstr(const string &str)
    {
        wprintw(window, str.c_str());
    }

    void Window::mvaddch_(int y, int x, const chtype ch)
    {
        mvwaddch(window, y, x, ch);
    }

    void Window::sbox()
    {
        box(window, ACS_VLINE, ACS_HLINE);
    }

    int Window::getch_()
    {
        return wgetch(window);
    }

    void Window::get_specific_ch(int c)
    {
        while (getch_() != c);
    }

    int Window::getch_(const vector<int> &cs)
    {

        while (true)
        {
            int c = getch_();
            for (int c_:cs)
            {
                if (c == c_) return c;
            }
        }
    }

    void Window::refresh_()
    {
        if (boxing) sbox();
        wrefresh(window);
    }

    void Window::move_cursor(int y, int x)
    {
        wmove(window, y, x);
    }

    void Window::keypad_on()
    {
        keypad(window, TRUE);
    }

    void Window::clear_from_cursor_to_eol()
    {
        wclrtoeol(window);
    }

    void Window::erase()
    {
        werase(window);
    }

    int Window::get_height() const
    {
        return height;
    }

    int Window::get_width() const
    {
        return width;
    }

    int Window::get_starty() const
    {
        return starty;
    }

    int Window::get_startx() const
    {
        return startx;
    }

    int Window::get_x() const
    {
        int y;
        int x;
        getyx(window, y, x);
        return x;
    }

    int Window::get_y() const
    {
        int y;
        int x;
        getyx(window, y, x);
        return y;
    }

    void Window::color_on(int color_id)
    {
        wattron(window, COLOR_PAIR(color_id));
    }


    void Window::color_off(int color_id)
    {
        wattroff(window, COLOR_PAIR(color_id));
    }

    void Window::attron_(int attr)
    {
        wattron(window, attr);
    }


    void Window::attroff_(int attr)
    {
        wattroff(window, attr);
    }
}
