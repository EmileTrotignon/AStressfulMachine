//
// Created by emile on 06/03/19.
//

#include <form.h>
#include <assert.h>

#include "GameTUI.h"
#include "ncurses_utilities.h"

GameTUI::GameTUI(const string &saves_dir_, const string &gamefiles_dir_) : Game(saves_dir_, gamefiles_dir_),
                                                                           typing_win(nullptr),
                                                                           instruction_win(nullptr),
                                                                           vm_input_win(nullptr),
                                                                           vm_output_win(nullptr),
                                                                           vm_memory_win(nullptr),
                                                                           vm_program_win(nullptr),
                                                                           looper(nullptr)
{
    typed_text = "";
}

void GameTUI::pick_saves()
{
    vector<string> possible_saves = save_picker->get_saves();
    int height = (int) possible_saves.size() + 2;
    WINDOW *save_picking = create_newwin(height, 25, 4, 4);
    string selected_save = possible_saves[menu(possible_saves, save_picking)];
    destroy_win(save_picking);
    refresh();
    game_sequence = new GameSequence(selected_save, gamefiles_dir);
}

void GameTUI::pick_level()
{

    vector<string> possible_levels = game_sequence->get_available_levels();
    game_sequence->select_level(possible_levels[menu(possible_levels, stdscr)]);
}

void GameTUI::play_level()
{
    typing_win = create_newwin(LINES / 2, COLS / 2, 0, COLS / 2);
    initialize_typing_win();
    keypad(typing_win, TRUE);

    instruction_win = create_newwin(LINES / 2, COLS / 2, 0, 0);
    fill_instructions();

    vm_input_win = create_newwin(LINES / 2, COLS / 4, LINES / 2, 0);
    vm_output_win = create_newwin(LINES / 2, COLS / 4, LINES / 2, COLS / 4);

    vm_program_win = create_newwin(LINES / 4, COLS / 2, LINES / 2, COLS / 2);
    vm_memory_win = create_newwin(LINES / 4, COLS / 2, LINES / 2 + LINES / 4, COLS / 2);

    looper = bind2nd(function<void(VirtualMachine *, GameTUI *)>(vm_looper), this);

    box(instruction_win, ACS_VLINE, ACS_HLINE);
    box(vm_input_win, ACS_VLINE, ACS_HLINE);
    box(vm_output_win, ACS_VLINE, ACS_HLINE);
    box(vm_program_win, ACS_VLINE, ACS_HLINE);
    box(vm_memory_win, ACS_VLINE, ACS_HLINE);
    box(typing_win, ACS_VLINE, ACS_HLINE);

    wrefresh(typing_win);
    wrefresh(instruction_win);
    wrefresh(vm_input_win);
    wrefresh(vm_output_win);
    wrefresh(vm_memory_win);
    wrefresh(vm_program_win);
    curs_set(1);
    wmove(typing_win, 2, 2);
    handle_typing();
}

void GameTUI::initialize_typing_win()
{
    wrefresh(typing_win);

}

void GameTUI::fill_instructions()
{
    mvwprintw(instruction_win, 1, 1, game_sequence->get_current_level()->get_instructions().c_str());
}

void GameTUI::handle_typing()
{
    /* char *(FIELD *field, int buffer_index); */
    int ch;
    refresh();
    auto cursor = typed_text.end();
    while ((ch = wgetch(typing_win)) != KEY_F(5))
    {
        switch (ch)
        {
            case KEY_RIGHT:
                if (cursor != typed_text.end())
                {
                    cursor++;
                }
                break;

            case KEY_LEFT:
                if (cursor != typed_text.begin())
                {
                    cursor--;
                }
                break;

            case KEY_BACKSPACE:
                if (cursor != typed_text.begin())
                {
                    typed_text.erase(cursor - 1, cursor);
                    cursor--;
                }
                break;
            default:
                if (isprint(ch))
                {
                    //if (cursor - typed_text.begin() > 15) getch();

                    //if (cursor - typed_text.begin() >= typed_text.capacity()) typed_text.resize(typed_text.capacity() * 2);
                    if (cursor < typed_text.end()) typed_text.insert(cursor, (char) ch);
                    else typed_text.append(string(1, (char) ch));
                    //if (cursor - typed_text.begin() > 15) getch();
                    cursor++;
                }
                break;

        }
        //getch();
        mvwprintw(typing_win, 2, 2, typed_text.c_str());
        wclrtoeol(typing_win);
        wmove(typing_win, 2, (int) (2 + cursor - typed_text.begin()));

    }
    bool b = false;
    try
    {
        b = game_sequence->get_current_level()->attempt(typed_text, looper);
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
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_GREEN);
    curs_set(0);
    box(stdscr, ACS_VLINE, ACS_HLINE);
    mvaddstr(1, 5, "A Stressful Machine\n");
    box(stdscr, ACS_VLINE, ACS_HLINE);
    getch();
    pick_saves();
    pick_level();
    play_level();
    endwin();
}

void vm_looper(VirtualMachine *vm, GameTUI *gi)
{
    mvwprintw(gi->instruction_win, 10, 2, "looper here");
    mvwprintw(gi->vm_memory_win, LINES / 8, 8, vm->program_to_string().c_str());
    print_program_to_win(gi->vm_program_win, vm);
    wrefresh(gi->vm_memory_win);
    wrefresh(gi->instruction_win);
    getch();

}

