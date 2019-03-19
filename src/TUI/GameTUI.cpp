//
// Created by emile on 06/03/19.
//

#include <form.h>

#include "GameTUI.h"

using namespace ncursespp;

void print_memory_to_win(Window &win, VirtualMachine *vm)
{
    win.erase();
    const vector<int> &memory = vm->get_memory();
    win.move_cursor(win.get_height() / 2, 2);
    for (auto i = memory.begin(); i < memory.end(); i++)
    {
        if (i - memory.begin() == vm->get_memory_ptr() - vm->get_memory().begin()) win.color_on(1);
        win.printstr(to_string(*i));
        if (i - memory.begin() == vm->get_memory_ptr() - vm->get_memory().begin()) win.color_off(1);
        printw(" ");
    }
    win.refresh_();
}


void print_input_to_win(Window &win, GameLevel *gl)
{
    win.erase();
    win.mvprintstr(2, 2, gl->get_input_as_string());
    win.refresh_();
}

void raw_vm_solution_out_callback(int output, GameTUI *gi)
{
    gi->vm_output_win->mvprintstr(gi->n_lines_attempt_output + 2, gi->vm_output_win->get_width() / 2 + 1,
                                  to_string(output));
    gi->vm_output_win->refresh_();
    gi->n_lines_attempt_output++;
}

void raw_vm_attempt_out_callback(int output, GameTUI *gi)
{
    gi->vm_output_win->mvprintstr(gi->n_lines_attempt_output + 2, 2, to_string(output));
    gi->vm_output_win->refresh_();
}

void raw_vm_callback(VirtualMachine *vm, GameTUI *gi, bool pause_at_each_it)
{
    print_memory_to_win(*(gi->vm_memory_win), vm);
    gi->typing_field->attron_char(vm->get_current_operator() - vm->get_program().begin(), COLOR_PAIR(1));
    gi->typing_win->refresh_();
    gi->typing_field->refresh_();
    if (pause_at_each_it) gi->vm_memory_win->getch_();
}

void raw_gl_callback(GameLevel *gl, GameTUI *gi, bool pause_at_each_it)
{

    print_input_to_win(*(gi->vm_input_win), gl);

    gi->vm_input_win->refresh_();

    if (pause_at_each_it) gi->vm_input_win->getch_();
}


GameTUI::GameTUI(const string &saves_dir_, const string &gamefiles_dir_) : Game(saves_dir_, gamefiles_dir_),
                                                                           typing_win(nullptr),
                                                                           instruction_win(nullptr),
                                                                           vm_input_win(nullptr),
                                                                           vm_output_win(nullptr),
                                                                           vm_memory_win(nullptr),
                                                                           vm_program_win(nullptr),
                                                                           level_picking_win(nullptr),
                                                                           save_picking_win(nullptr),
                                                                           typing_field(nullptr),
                                                                           success_menu_win(nullptr)
{
}

GameTUI::~GameTUI()
{
    delete typing_win;
    delete typing_field;
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

    if (save_picking_win == nullptr)
    {
        save_picking_win = new Window(stdscr_->get_height(), stdscr_->get_width(), 0, 0);
    }
    Menu save_picking(possible_saves, save_picking_win, "Please pick a savefile :");

    string selected_save = possible_saves[save_picking.select_item()];
    game_sequence = new GameSequence(selected_save, gamefiles_dir);

}

void GameTUI::pick_level()
{
    vector<string> possible_levels = game_sequence->get_available_levels();

    if (level_picking_win == nullptr)
    {
        level_picking_win = new Window(stdscr_->get_height(), stdscr_->get_width(), 0, 0);
    }

    Menu level_picking(possible_levels, level_picking_win, "Please pick a level :");
    game_sequence->select_level(possible_levels[level_picking.select_item()]);

    delete typing_win;
    delete typing_field;
    delete instruction_win;
    delete vm_input_win;
    delete vm_output_win;
    delete vm_memory_win;

    const int h = stdscr_->get_height();
    const int w = stdscr_->get_width();

    typing_win = new Window(h / 2, w / 2, 0, w / 2, true);
    typing_field = new Field(vector<int>({KEY_F(5), KEY_F(6), KEY_F(7)}), typing_win->get_height() - 4,
                             typing_win->get_width() - 4,
                             typing_win->get_starty() + 2, typing_win->get_startx() + 2);
    instruction_win = new Window(h / 2, w / 2, 0, 0, true);
    fill_instructions();

    vm_input_win = new Window(h / 2, w / 4, h / 2, 0, true);
    vm_output_win = new Window(h / 2, w / 4, h / 2, w / 4, true);

    vm_program_win = new Window(h / 4, w / 2, h / 2, w / 2, true);
    vm_memory_win = new Window(h / 4, w / 2, h / 2 + h / 4, w / 2, true);

}

void GameTUI::play_level()
{
    typing_win->refresh_();
    instruction_win->refresh_();
    vm_input_win->refresh_();
    vm_output_win->refresh_();
    vm_memory_win->refresh_();
    vm_program_win->refresh_();
    typing_win->move_cursor(2, 2);
    handle_typing();
}

void GameTUI::fill_instructions()
{
    instruction_win->mvprintstr(1, 2, game_sequence->get_current_level()->get_instructions());
}

void GameTUI::handle_typing()
{
    using namespace placeholders;

    function<void(VirtualMachine *)> vm_callback;
    function<void(GameLevel *)> gl_callback;
    function<void(int)> vm_output_attempt_callback = bind(function<void(int, GameTUI *)>(raw_vm_attempt_out_callback),
                                                          _1, this);
    function<void(int)> vm_output_solution_callback = bind(function<void(int, GameTUI *)>(raw_vm_solution_out_callback),
                                                           _1, this);

    print_input_to_win(*(vm_input_win), game_sequence->get_current_level());

    int exit_key = typing_field->type();
    vm_output_win->erase();
    bool success;
    try
    {
        switch (exit_key)
        {
            case KEY_F(5):
                vm_callback = bind(function<void(VirtualMachine *, GameTUI *, bool)>(raw_vm_callback), _1, this, true);
                gl_callback = bind(function<void(GameLevel *, GameTUI *, bool)>(raw_gl_callback), _1, this, true);
                break;

            case KEY_F(6):
                vm_callback = bind(function<void(VirtualMachine *, GameTUI *, bool)>(raw_vm_callback), _1, this, false);
                gl_callback = bind(function<void(GameLevel *, GameTUI *, bool)>(raw_gl_callback), _1, this, true);
                break;
            case KEY_F(7):
                vm_callback = bind(function<void(VirtualMachine *, GameTUI *, bool)>(raw_vm_callback), _1, this, false);
                gl_callback = bind(function<void(GameLevel *, GameTUI *, bool)>(raw_gl_callback), _1, this, false);

            default:
                vm_callback = nullptr;
                gl_callback = nullptr;

        }
        success = game_sequence->get_current_level()->attempt(typing_field->get_typed_text(),
                                                              vm_callback,
                                                              gl_callback,
                                                              vm_output_attempt_callback,
                                                              vm_output_solution_callback);
        vm_memory_win->erase();
        vm_memory_win->refresh_();
    } catch (const VirtualMachineException &e)
    {
        success = false;
    }
    n_lines_attempt_output = 0;
    if (success)
    {
        handle_success();
    } else
    {
        handle_failure();
    }

}

void GameTUI::handle_success()
{

    vector<string> options{"Retry this level", "Play another level", "Quit the game"};

    if (success_menu_win == nullptr)
        success_menu_win = new Window(stdscr_->get_height(), stdscr_->get_width(), 0, 0);

    auto menu = new Menu(options, success_menu_win,
                         "Congratulation, you have solved this level. What do you want to do now ?");
    switch (menu->select_item())
    {
        default:
            break;
        case 0:
            play_level();
            break;
        case 1:
            pick_level();
            play_level();
            break;
    }

}

void GameTUI::handle_failure()
{
    handle_typing();
}

void GameTUI::play()
{
    initscr_();
    cbreak();
    noecho();
    stdscr_->keypad_on();
    if (has_colors() == FALSE)
    {
        endwin();
        cout << "Your terminal does not support color" << endl;
        exit(1);
    }
    start_color();
    init_pair(1, COLOR_BLACK, COLOR_GREEN);
    curs_set(0);
    Window starting_screen(stdscr_->get_height(), stdscr_->get_width(), 0, 0);
    starting_screen.printstr_in_middle("Welcome to A Stressful Machine. Press any key to start the game...");
    starting_screen.refresh_();
    starting_screen.getch_();
    pick_saves();
    pick_level();
    play_level();
    endwin_();
}

