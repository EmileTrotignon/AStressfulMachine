//
// Created by emile on 14/03/19.
//

#include "NcursesMenu.h"

namespace ncursespp
{
    NcursesMenu::NcursesMenu(const vector<string> &options_, int height_, int width_, int startx_, int starty_,
                             bool boxing_) : NcursesWindow(height_, width_, startx_, starty_, boxing_),
                                             options(options_)
    {
        refresh();
        keypad_on();
        for (unsigned int i = 0; i < options.size(); i++)
        {
            if (i == options.size() - 1) attron_(A_STANDOUT);
            else
                attroff_(A_STANDOUT);
            printstr_centered(i + 1, options[i]);
        }
        attroff_(A_STANDOUT);
        int ch;
        selected_item = (int) options.size() - 1;
        while ((ch = getch_()) != '\n')
        {
            // Reprint selected item in order to redo the highlighting
            printstr_centered(selected_item + 1, options[selected_item]);
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
            printstr_centered(selected_item + 1, options[selected_item]);
            attroff_(A_STANDOUT);
            refresh();
        }
    }


    int NcursesMenu::get_selected_item()
    {
        return selected_item;
    }

}