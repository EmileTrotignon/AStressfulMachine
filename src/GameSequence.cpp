//
// Created by emile on 05/03/19.
//

#include "GameSequence.h"

GameSequence::GameSequence(const string &savename, const string &gamefiles_dir_) : gamefiles_dir(gamefiles_dir_)
{
    available_levels = filesystem_ls(gamefiles_dir + "/levels");
}

void GameSequence::select_level(const string &level)
{
    delete current_level;
    current_level = new GameLevel(gamefiles_dir, level);
}

vector<string> GameSequence::get_available_levels() const
{
    return available_levels;
}

GameLevel *GameSequence::get_current_level()
{
    return current_level;
}