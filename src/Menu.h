//
// Created by emile on 14/03/19.
//

#ifndef A_STRESSFUL_MACHINE_NCURSESMENU_H
#define A_STRESSFUL_MACHINE_NCURSESMENU_H

#include "Window.h"

namespace ncursespp
{
    class Menu : protected Window
    {
    private:
        const vector<string> options;

        int selected_item;

    public:
        Menu(const vector<string> &options, int height, int width, int startx, int starty, bool boxing = false);

        Menu(const vector<string> &options, Window *master_win, const string &message);

        int select_item();
    };
}

#endif //A_STRESSFUL_MACHINE_NCURSESMENU_H
