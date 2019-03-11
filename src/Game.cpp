//
// Created by emile on 06/03/19.
//

#include "Game.h"

Game::Game(const string &save_dir, const string &gamefiles_dir) : game_sequence(nullptr)
{
    save_picker = new SavePicker(save_dir, gamefiles_dir);
}