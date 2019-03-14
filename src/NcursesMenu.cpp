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
        if (i == options.size() - 1) attron_(A_STANDOUT);
        else
            attroff_(A_STANDOUT);
        mvprintw(i + 1, 2, options[i].c_str());
    }
    attroff_(A_STANDOUT);
    int ch;
    selected_item = (int) options.size() - 1;
    while ((ch = getch_()) != '\n')
    {
        // Reprint selected item in order to redo the highlighting
        mvprintw(selected_item + 1, 2, options[selected_item].c_str());
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
        attron_(A_STANDOUT);
        mvprintw(selected_item + 1, 2, options[selected_item].c_str());
        attroff_(A_STANDOUT);
        refresh();
    }
}


int NcursesMenu::get_selected_item()
{
    return selected_item;
}

