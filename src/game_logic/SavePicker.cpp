//
// Created by emile on 06/03/19.
//

#include "SavePicker.h"
#include <ncurses.h>
#include <assert.h>

namespace fs = std::filesystem;

SavePicker::SavePicker(const string &save_dir, const string &gamefiles_) : gamefiles(gamefiles_)
{
    saves = filesystem_ls(save_dir);

}

vector<string> SavePicker::get_saves() const
{
    return saves;
}

GameSequence SavePicker::select_save(string save) const
{
    return GameSequence(save, gamefiles);
}