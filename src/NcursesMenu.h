//
// Created by emile on 14/03/19.
//

#ifndef A_STRESSFUL_MACHINE_NCURSESMENU_H
#define A_STRESSFUL_MACHINE_NCURSESMENU_H

#include "NcursesWindow.h"

namespace ncursespp
{
    class NcursesMenu : protected NcursesWindow
    {
    private:
        const vector<string> options;

        int selected_item;

    public:
        NcursesMenu(const vector<string> &options, int height, int width, int startx, int starty, bool boxing = false);

        NcursesMenu(const vector<string> &options, NcursesWindow *master_win, const string &message);

        int select_item();
    };
}

#endif //A_STRESSFUL_MACHINE_NCURSESMENU_H
