//
// Created by emile on 06/03/19.
//

#include "SavePicker.h"

namespace fs = std::filesystem;

SavePicker::SavePicker(const string &save_dir)
{
    saves = filesystem_ls(save_dir);
}

vector<string> SavePicker::get_saves() const
{
    return saves;
}

GameSequence SavePicker::select_save(string save) const
{
    return GameSequence(save);
}