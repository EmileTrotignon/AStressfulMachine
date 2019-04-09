//
// Created by emile on 06/03/19.
//

#ifndef A_STRESSFUL_MACHINE_SAVEPICKER_H
#define A_STRESSFUL_MACHINE_SAVEPICKER_H

#include <iostream>
#include <map>
#include <filesystem>

#include "GameSequence.h"

/**
 * SavePicker lists the available savefiles and let you pick one.
 */

using namespace std;

class SavePicker
{
private:

    vector<string> saves;
    string gamefiles;
    fs::path save_dir;

public:

    SavePicker(const string &save_dir, const string &gamefiles);

    vector<string> get_saves() const;

    GameSequence select_save(string save) const;

};


#endif //A_STRESSFUL_MACHINE_SAVEPICKER_H
