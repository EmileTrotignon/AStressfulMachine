//
// Created by emile on 06/03/19.
//

#ifndef A_STRESSFUL_MACHINE_SAVEPICKER_H
#define A_STRESSFUL_MACHINE_SAVEPICKER_H

#include <iostream>
#include <map>

#include "GameSequence.h"

/**
 * SavePicker lists the available savefiles and let you pick one.
 */

using namespace std;

class SavePicker
{
private:

    map<string, string> saves;

public:

    SavePicker(const string &save_dir, const string &gamefiles_dir);

    map <string, string> get_saves();

    GameSequence select_save(string save);

    GameSequence tui_select_save();
};


#endif //A_STRESSFUL_MACHINE_SAVEPICKER_H
