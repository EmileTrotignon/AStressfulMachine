//
// Created by emile on 14/03/19.
//

#include "NcursesMenu.h"


NcursesMenu::NcursesMenu(const vector<string> &options_, int height_, int width_, int startx_, int starty_,
                         bool boxing_) : NcursesWindow(height_, width_, startx_, starty_, boxing_), options(options_)
{
    keypad_on();
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

