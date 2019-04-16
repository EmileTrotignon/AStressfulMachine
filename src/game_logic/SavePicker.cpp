//
// Created by emile on 06/03/19.
//

#include "SavePicker.h"
#include <assert.h>

namespace fs = std::filesystem;

SavePicker::SavePicker(const fs::path &save_dir_, const fs::path &gamefiles_) : save_dir(save_dir_),
                                                                                gamefiles(gamefiles_)
{
    saves = filesystem_ls(save_dir);

}

vector<string> SavePicker::get_saves() const
{
    return saves;
}

GameSequence SavePicker::select_save(string save) const
{
    return GameSequence(save, save_dir, gamefiles);
}