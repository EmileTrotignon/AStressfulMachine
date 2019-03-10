//
// Created by emile on 06/03/19.
//

#include <form.h>

#include "GameTUI.h"
#include "ncurses_utilities.h"

WINDOW *create_newwin(int height, int width, int starty, int startx);

void destroy_win(WINDOW *local_win);

GameTUI::GameTUI(const string &saves_dir_, const string &gamefiles_dir_) : Game(saves_dir_, gamefiles_dir_), typing_win(
        nullptr), instruction_win(nullptr), vm_input_win(nullptr), vm_output_win(nullptr), vm_memory_win(nullptr),
                                                                           vm_program_win(nullptr), looper(nullptr),
                                                                           field_content(
                                                                                   "")
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
    vector<string> possible_levels = game_sequence->get_available_levels();
    game_sequence->select_level(possible_levels[menu(possible_levels, stdscr)]);
}

void GameTUI::play_level()
{
    typing_win = create_newwin(LINES / 2, COLS / 2, 0, COLS / 2);
    box(typing_win, ACS_VLINE, ACS_HLINE);
    initialize_typing_win();

    instruction_win = create_newwin(LINES / 2, COLS / 2, 0, 0);
    box(instruction_win, ACS_VLINE, ACS_HLINE);
    fill_instructions();

    vm_input_win = create_newwin(LINES / 2, COLS / 4, LINES / 2, 0);
    box(vm_input_win, ACS_VLINE, ACS_HLINE);

    vm_output_win = create_newwin(LINES / 2, COLS / 2, COLS / 4, LINES / 2);
    box(vm_output_win, ACS_VLINE, ACS_HLINE);

    vm_program_win = create_newwin(LINES / 4, COLS / 2, LINES / 2, COLS / 2);
    box(vm_program_win, ACS_VLINE, ACS_HLINE);

    vm_memory_win = create_newwin(LINES / 4, COLS / 2, LINES / 4, COLS / 2);
    box(vm_memory_win, ACS_VLINE, ACS_HLINE);
    looper = bind2nd(vm_looper, this);
    handle_typing();
}

void GameTUI::initialize_typing_win()
{
    typing_field = new_field(LINES / 2 - 2, COLS / 2 - 2, 1, 1, 0, 0);


    typing_form = new_form(&typing_field);
    set_form_win(typing_form, typing_win);
    post_form(typing_form);
    wrefresh(typing_win);
}

void GameTUI::fill_instructions()
{
    mvwprintw(instruction_win, 1, 1, game_sequence->get_current_level().get_instructions().c_str());
}

void GameTUI::handle_typing()
{
    /* char *(FIELD *field, int buffer_index); */
    int ch;
    while ((ch = wgetch(typing_win)) != KEY_F(5))
    {
        if (isprint(ch)) form_driver(typing_form, ch);
    }
    field_content = (string) field_buffer(typing_field, 0);
    bool b = false;
    try
    {
        b = game_sequence->get_current_level().attempt(field_content);
    } catch (const VirtualMachineException &e)
    {

    }
    if (b)
    {
        pick_level();
    } else
    {
        handle_typing();
    }

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
    pick_level();
    endwin();
}

void vm_looper(VirtualMachine *vm, GameTUI *gi)
{
    mvwprintw(gi->vm_program_win, LINES / 8, 2, vm->program_to_string().c_str());
    mvwprintw(gi->vm_memory_win, LINES / 8, 8, vm->program_to_string().c_str());

}