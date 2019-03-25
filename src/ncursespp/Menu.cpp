//
// Created by emile on 14/03/19.
//

#include <algorithm>
#include "Menu.h"

bool comp_str(const string &s1, const string &s2)
{
    return s1.size() < s2.size();
}

size_t size_of_longest_string(const vector<string> &vs)
{
    return max_element(vs.begin(), vs.end(), comp_str)->size();
}

namespace ncursespp
{
    Menu::Menu(const vector<string> &options_, int height_, int width_, int startx_, int starty_,
               bool boxing_) : Window(height_, width_, startx_, starty_, boxing_),
                               options(options_)
    {

    }

    Menu::Menu(const vector<string> &options_, Window *master_win, const string &message) :
            options(options_),
            Window(master_win,
                   (int) options_.size() + 2,
                   (int) size_of_longest_string(options_) + 8,
                   master_win->get_height() / 2 - ((int) options_.size() + 2) / 2,
                   master_win->get_width() / 2 - ((int) size_of_longest_string(options_) + 8) / 2,
                   true)
    {
        master_win->printstr_centered(starty / 2, message);
        master_win->refresh_();
        keypad_on();
    }

    int Menu::select_item()
    {

        for (unsigned int i = 0; i < options.size(); i++)
        {
            if (i == 0) attron_(A_STANDOUT);
            else attroff_(A_STANDOUT);
            printstr_centered(i + 1, options[i]);
        }
        attroff_(A_STANDOUT);
        int ch;
        selected_item = 0;

        refresh_();

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
            this->refresh_();
        }
        return selected_item;
    }


}