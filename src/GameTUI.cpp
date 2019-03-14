//
// Created by emile on 06/03/19.
//

#include <form.h>
#include <assert.h>

#include "GameTUI.h"
#include "ncurses_utilities.h"
#include "NcursesMenu.h"

GameTUI::GameTUI(const string &saves_dir_, const string &gamefiles_dir_) : Game(saves_dir_, gamefiles_dir_),
                                                                           typing_win(nullptr),
                                                                           instruction_win(nullptr),
                                                                           vm_input_win(nullptr),
                                                                           vm_output_win(nullptr),
                                                                           vm_memory_win(nullptr),
                                                                           vm_program_win(nullptr)
{
    typed_text = "";
}

GameTUI::~GameTUI()
{
    delete typing_win;
    delete instruction_win;
    delete vm_input_win;
    delete vm_output_win;
    delete vm_memory_win;
    delete vm_program_win;
    delete game_sequence;
}

void GameTUI::pick_saves()
{
    vector<string> possible_saves = save_picker->get_saves();
    int height = (int) possible_saves.size() + 2;
    auto save_picking = new NcursesMenu(possible_saves, height, 25, 4, 4, true);
    string selected_save = possible_saves[save_picking->get_selected_item()];
    delete save_picking;
    game_sequence = new GameSequence(selected_save, gamefiles_dir);
}

void GameTUI::pick_level()
{
    vector<string> possible_levels = game_sequence->get_available_levels();
    int height = (int) possible_levels.size() + 2;
    auto level_picking = new NcursesMenu(possible_levels, height, 25, 4, 4, true);
    game_sequence->select_level(possible_levels[level_picking->get_selected_item()]);
    delete level_picking;
}

void GameTUI::play_level()
{
    typing_win = new NcursesWindow(LINES / 2, COLS / 2, 0, COLS / 2, true);

    typing_win->keypad_on();

    instruction_win = new NcursesWindow(LINES / 2, COLS / 2, 0, 0, true);
    fill_instructions();

    vm_input_win = new NcursesWindow(LINES / 2, COLS / 4, LINES / 2, 0, true);
    vm_output_win = new NcursesWindow(LINES / 2, COLS / 4, LINES / 2, COLS / 4, true);

    vm_program_win = new NcursesWindow(LINES / 4, COLS / 2, LINES / 2, COLS / 2, true);
    vm_memory_win = new NcursesWindow(LINES / 4, COLS / 2, LINES / 2 + LINES / 4, COLS / 2, true);

    typing_win->refresh();
    instruction_win->refresh();
    vm_input_win->refresh();
    vm_output_win->refresh();
    vm_memory_win->refresh();
    vm_program_win->refresh();
    typing_win->move_cursor(2, 2);
    handle_typing();
}

void GameTUI::fill_instructions()
{
    instruction_win->mvprintstr(1, 1, game_sequence->get_current_level()->get_instructions());
}

void GameTUI::handle_typing()
{
    /* char *(FIELD *field, int buffer_index); */
    curs_set(1);
    int ch;
    refresh();
    unsigned long cursor = typed_text.size();
    while ((ch = typing_win->getch_()) != KEY_F(5))
    {
        switch (ch)
        {
            case KEY_RIGHT:
                if (cursor < typed_text.size())
                {
                    cursor++;
                }
                break;

            case KEY_LEFT:
                if (cursor > 0)
                {
                    cursor--;
                }
                break;

            case KEY_BACKSPACE:
                if (cursor != 0)
                {
                    typed_text.erase(cursor - 1, 1);
                    cursor--;
                }
                break;

            case KEY_DC:
                if (cursor != typed_text.size())
                {
                    typed_text.erase(cursor, 1);
                }
                break;

                    default:
                if (isprint(ch))
                {
                    //if (cursor - typed_text.begin() > 15) getch();

                    //if (cursor - typed_text.begin() >= typed_text.capacity()) typed_text.resize(typed_text.capacity() * 2);
                    typed_text.insert(typed_text.begin() + cursor, (char) ch);

                    //if (cursor - typed_text.begin() > 15) getch();
                    cursor++;
                }
                break;

        }
        typing_win->move_cursor(2, 2);
        typing_win->clear_from_cursor_to_eol();
        typing_win->mvprintstr(2, 2, typed_text);
        typing_win->refresh();
        typing_win->move_cursor(2, (int) (2 + (cursor)));


    }
    curs_set(0);
    bool b = false;
    try
    {
        vm_callback = bind2nd(function<void(VirtualMachine *, GameTUI *)>(raw_vm_callback), this);
        gl_callback = bind2nd(function<void(GameLevel *, GameTUI *)>(raw_gl_callback), this);
        b = game_sequence->get_current_level()->attempt(typed_text, vm_callback, gl_callback);
    } catch (const VirtualMachineException &e)
    {

    }
    if (b)
    {
        handle_success();
    } else
    {
        handle_typing();
    }

}

void GameTUI::handle_success()
{
    vector<string> options{"Retry this level", "Play another level", "Quit the game"};
    int h = 25;
    int w = (int) options.size();
    auto menu = new NcursesMenu(options, h, w, COLS / 2 - h, LINES / 2 - w);
    switch (menu->get_selected_item())
    {
        default:
            break;
        case 0:
            play_level();
        case 1:
            pick_level();
    }

}

void GameTUI::play()
{
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    if (has_colors() == FALSE)
    {
        endwin();
        cout << "Your terminal does not support color" << endl;
        exit(1);
    }
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

void raw_vm_callback(VirtualMachine *vm, GameTUI *gi)
{
    gi->vm_memory_win->print_memory_to_win(vm);
    gi->vm_program_win->print_program_to_win(vm);
    getch();
}

void raw_gl_callback(GameLevel *gl, GameTUI *gi)
{
    gi->vm_input_win->print_input_to_win(gl);
    //getch();
}
