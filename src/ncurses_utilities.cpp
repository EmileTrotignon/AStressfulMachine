//
// Created by emile on 10/03/19.
//

#include "ncurses_utilities.h"
#include "GameLevel.h"
#include "NcursesWindow.h"

int menu(const vector<string> &options, WINDOW *win)
{
    keypad(win, TRUE);
    for (unsigned int i = 0; i < options.size(); i++)
    {
        if (i == options.size() - 1) wattron(win, A_STANDOUT);
        else
            wattroff(win, A_STANDOUT);
        mvwprintw(win, i + 1, 2, options[i].c_str());
    }
    wattroff(win, A_STANDOUT);
    int ch;
    int selected_item = (int) options.size() - 1;
    while ((ch = wgetch(win)) != '\n')
    {
        // Reprint selected item in order to redo the highlighting
        mvwprintw(win, selected_item + 1, 2, options[selected_item].c_str());
        switch (ch)
        {
            case KEY_UP:
                selected_item--;
                selected_item = (selected_item < 0) ? (int) options.size() - 1 : selected_item;
                break;
            case KEY_DOWN:
                selected_item++;
                selected_item = (selected_item >= options.size()) ? 0 : selected_item;
                break;
            default:
                break;
        }
        //Highlight the current item
        wattron(win, A_STANDOUT);
        mvwprintw(win, selected_item + 1, 2, options[selected_item].c_str());
        wattroff(win, A_STANDOUT);
    }
    werase(win);
    wrefresh(win);
    return selected_item;
}

WINDOW *create_newwin(int height, int width, int starty, int startx)
{
    WINDOW *local_win;

    local_win = newwin(height, width, starty, startx);
    sbox(local_win);
    wrefresh(local_win);
    return local_win;
}

void sbox(WINDOW *win)
{
    box(win, ACS_VLINE, ACS_HLINE);
}

void destroy_win(WINDOW *local_win)
{
    /* box(local_win, ' ', ' '); : This won't produce the desired
     * result of erasing the window. It will leave it's four corners
     * and so an ugly remnant of window.
     */
    wborder(local_win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    /* The parameters taken are
     * 1. win: the window on which to operate
     * 2. ls: character to be used for the left side of the window
     * 3. rs: character to be used for the right side of the window
     * 4. ts: character to be used for the top side of the window
     * 5. bs: character to be used for the bottom side of the window
     * 6. tl: character to be used for the top left corner of the window
     * 7. tr: character to be used for the top right corner of the window
     * 8. bl: character to be used for the bottom left corner of the window
     * 9. br: character to be used for the bottom right corner of the window
     */
    werase(local_win);
    wrefresh(local_win);
    delwin(local_win);
}

void mvwprintstr(WINDOW *win, int y, int x, string str)
{
    istringstream strs(str);
    string buff;
    while (!strs.eof())
    {
        getline(strs, buff);
        mvwprintw(win, y, x, buff.c_str());
        buff = "";
        y++;
    }
}

void print_program_to_win(WINDOW *win, VirtualMachine *vm)
{
    const string &program = vm->get_program();

    for (auto i = program.begin(); i < program.end(); i++)
    {
        if (i == vm->get_current_operator())
        {
            wattron(win, COLOR_PAIR(1));
        }
        mvwaddch(win, LINES / 8, (int) (2 + i - program.begin()), (const chtype) *i);
        if (i == vm->get_current_operator())
        {
            wattroff(win, COLOR_PAIR(1));
        }
    }
    wrefresh(win);
}

void print_memory_to_win(NcursesWindow *win, VirtualMachine *vm)
{
    const vector<int> &memory = vm->get_memory();
    win->move_cursor(win->get_height() / 2, 2);
    for (auto i = memory.begin(); i < memory.end(); i++)
    {
        if (i - memory.begin() == vm->get_memory_ptr() - vm->get_memory().begin()) win->color_on(1);
        win->printw("%d", *i);
        if (i - memory.begin() == vm->get_memory_ptr() - vm->get_memory().begin()) win->color_off(1);
        win->printw(" ");
    }
    win->refresh();
}


void print_input_to_win(NcursesWindow *win, GameLevel *gl)
{
    win->clear();
    win->mvprintstr(2, 2, gl->get_input_as_string());
    win->refresh();
}

