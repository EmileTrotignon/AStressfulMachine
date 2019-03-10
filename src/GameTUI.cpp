//
// Created by emile on 06/03/19.
//

#include "GameTUI.h"
#include "ncurses_utilities.h"

GameTUI::GameTUI(const string &saves_dir_, const string &gamefiles_dir_) : Game(saves_dir_, gamefiles_dir_)
{
}

void GameTUI::pick_saves()
{
    vector<string> possible_saves = save_picker->get_saves();
    string selected_save = possible_saves[menu(possible_saves, stdscr)];
    game_sequence = new GameSequence(selected_save, "data/gamefiles/");
}

void GameTUI::pick_level()
{
    vector<string> possible_levels;
}

void GameTUI::play()
{
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    box(stdscr, 0, 0);
    printw("Starting game of A Stressful Machine\n");
    pick_saves();
    endwin();
}