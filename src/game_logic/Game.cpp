#include <utility>

//
// Created by emile on 06/03/19.
//

#include "Game.h"

Game::Game(const fs::path &save_dir, fs::path gamefiles_dir_) : game_sequence(nullptr),
                                                                gamefiles_dir(std::move(gamefiles_dir_))
{
    save_picker = new SavePicker(save_dir, gamefiles_dir);
}