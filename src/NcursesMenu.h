//
// Created by emile on 14/03/19.
//

#ifndef A_STRESSFUL_MACHINE_NCURSESMENU_H
#define A_STRESSFUL_MACHINE_NCURSESMENU_H

#include "NcursesWindow.h"

class NcursesMenu : public NcursesWindow
{
private:
    const vector<string> options;

public:
    NcursesMenu(const vector<string> &options, int height, int width, int startx, int starty, bool boxing = false);

    int get_choice();
};


#endif //A_STRESSFUL_MACHINE_NCURSESMENU_H
