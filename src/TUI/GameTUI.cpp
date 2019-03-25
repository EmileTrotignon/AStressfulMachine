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
        win.printstr(" ");
    }
    win.refresh_();
}


void print_input_to_win(Window &win, GameLevel *gl)
{
    win.erase();
    win.mvprint_multiline_str(2, 2, gl->get_input_as_string());
    win.refresh_();
}

void raw_vm_solution_out_callback(int output, GameTUI *gi)
{
    gi->vm_output_solution_win->mvprint_multiline_str(gi->n_lines_attempt_output, 0, to_string(output));
    gi->vm_output_solution_win->refresh_();
    gi->n_lines_attempt_output++;
}

void raw_vm_attempt_out_callback(int output, GameTUI *gi)
{
    gi->vm_output_attempt_win->mvprint_multiline_str(gi->n_lines_attempt_output, 0, to_string(output));
    gi->vm_output_attempt_win->refresh_();
}

void raw_vm_callback(VirtualMachine *vm, GameTUI *gi, bool pause_at_each_it)
{
    print_memory_to_win(*(gi->vm_memory_win), vm);
    (*(gi->current_field))->attron_char(vm->get_current_operator() - vm->get_program().begin(), COLOR_PAIR(1));
    gi->typing_win->refresh_();
    (*(gi->current_field))->refresh_();
    if (pause_at_each_it)
    {

        switch (gi->vm_input_win->getch_({'q', '\n'}))
        {
            case 'q':
                throw UserInterrupt();

            case '\n':
                break;

            default:
                break;
        }
    } else if (gi->vm_input_win->nodelay_getch() == 'q')
    {
        throw UserInterrupt();
    }
}

void raw_gl_callback(GameLevel *gl, GameTUI *gi, bool pause_at_each_it)
{

    print_input_to_win(*(gi->vm_input_win), gl);

    gi->vm_input_win->refresh_();

    if (pause_at_each_it)
    {

        switch (gi->vm_input_win->getch_({'q', '\n'}))
        {
            case 'q':
                throw UserInterrupt();

            case '\n':
                break;

            default:
                break;
        }
    }
}


GameTUI::GameTUI(const string &saves_dir_, const string &gamefiles_dir_) : Game(saves_dir_, gamefiles_dir_),
                                                                           control_hint_win(nullptr),
                                                                           typing_win(nullptr),
                                                                           instruction_win(nullptr),
                                                                           vm_input_win(nullptr),
                                                                           vm_output_win(nullptr),
                                                                           vm_output_attempt_win(nullptr),
                                                                           vm_output_solution_win(nullptr),
                                                                           vm_memory_win(nullptr),
                                                                           vm_message_win(nullptr),
                                                                           level_picking_win(nullptr),
                                                                           save_picking_win(nullptr),
                                                                           typing_field({nullptr}),
                                                                           current_field(typing_field.begin()),
                                                                           success_menu_win(nullptr)
{
}

GameTUI::~GameTUI()
{
    delete typing_win;
    for (Field *f : typing_field)
    {
        delete f;
    }
    delete instruction_win;
    delete vm_input_win;
    delete vm_output_win;
    delete vm_output_attempt_win;
    delete vm_output_solution_win;
    delete vm_memory_win;
    delete vm_message_win;
    delete game_sequence;
    delete control_hint_win;
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
    game_sequence->select_level(level_picking.select_item());

    const int h = stdscr_->get_height();
    const int w = stdscr_->get_width();

    delete control_hint_win;
    delete typing_win;
    typing_win = new Window(h / 2, w / 2, 0, w / 2, true);
    for (auto i = typing_field.begin(); i != typing_field.end(); i++)
    {
        delete *i;
        *i = new Field(vector<int>({KEY_F(1), KEY_F(5), KEY_F(6), KEY_F(7), KEY_F(12)}), typing_win->get_height() - 4,
                       typing_win->get_width() - 4,
                       typing_win->get_starty() + 2, typing_win->get_startx() + 2);
    }

    current_field = typing_field.begin();
    get_attempts_from_gamelevel();

    delete instruction_win;
    delete vm_input_win;
    delete vm_output_win;
    delete vm_output_attempt_win;
    delete vm_output_solution_win;
    delete vm_memory_win;
    delete vm_message_win;


    control_hint_win = new Window(1, w, h - 1, 0);

    instruction_win = new Window(h / 2, w / 2, 0, 0, true);
    fill_instructions();

    vm_input_win = new Window(h / 2 - 1, w / 4, h / 2, 0, true);
    vm_output_win = new Window(h / 2 - 1, w / 4, h / 2, w / 4, true);
    vm_output_attempt_win = new Window(vm_output_win,
                                       vm_output_win->get_height() - 3,
                                       vm_output_win->get_width() / 2 - 2,
                                       2,
                                       2);

    vm_output_solution_win = new Window(vm_output_win,
                                        vm_output_win->get_height() - 3,
                                        vm_output_win->get_width() / 2 - 2,
                                        2,
                                        vm_output_win->get_width() / 2 + 1);

    vm_message_win = new MessageStack(h / 4, w / 2, h / 2, w / 2, true);
    vm_memory_win = new Window(h / 4 - 1, w / 2, h / 2 + h / 4, w / 2, true);
    draw_title();
}

void GameTUI::play_level()
{
    control_hint_win->refresh_();

    const int tab_width = int(((*current_field)->get_width() - 2) / typing_field.size());

    for (int i = 0; i < typing_field.size(); i++)
    {
        if (i == current_field - typing_field.begin()) typing_win->color_on(2);
        typing_win->mvprint_line(1, 1 + tab_width / 2 + i * tab_width, "[TAB #" + to_string(i) + "]");
        if (i == current_field - typing_field.begin()) typing_win->color_off(2);
    }
    typing_win->refresh_();
    instruction_win->refresh_();
    vm_input_win->refresh_();


    vm_output_win->refresh_();
    vm_output_solution_win->refresh_();
    vm_output_attempt_win->refresh_();

    vm_memory_win->refresh_();
    vm_message_win->refresh_();
    typing_win->move_cursor(2, 2);
    handle_typing();
}

void GameTUI::fill_instructions()
{
    instruction_win->mvprint_multiline_str(1, 2, (*game_sequence->get_current_level())->get_instructions());
}

void GameTUI::draw_title()
{

    instruction_win->mvprint_line(1, 2, "Instructions :");
    vm_output_win->mvprint_line(1, 2, "Your output :");
    vm_output_win->mvprint_line(1, vm_output_win->get_width() / 2 + 1, "Expected output :");
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

    print_input_to_win(*(vm_input_win), *(game_sequence->get_current_level()));

    control_hint_win->erase();
    control_hint_win->mvprint_multiline_str(0, 1, "When you're done, execute your code with: [F5] Step by step    "
                                                  "[F6] Input block by input block    "
                                                  "[F7] Fullspeed");
    control_hint_win->refresh_();
    int exit_key = (*current_field)->type();
    vm_output_attempt_win->erase();
    vm_output_solution_win->erase();
    vm_output_solution_win->refresh_();
    vm_output_attempt_win->refresh_();

    bool success;
    try
    {
        switch (exit_key)
        {
            case KEY_F(1):
                if (current_field != typing_field.begin()) current_field--;
                else current_field = typing_field.end() - 1;
                play_level();
                send_typed_texts_to_gamelevel();
                game_sequence->save_to_save();
                return;

            case KEY_F(12):
                if (current_field + 1 != typing_field.end()) current_field++;
                else current_field = typing_field.begin();
                play_level();
                send_typed_texts_to_gamelevel();
                game_sequence->save_to_save();
                return;

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
        send_typed_texts_to_gamelevel();
        game_sequence->save_to_save();
        control_hint_win->erase();
        control_hint_win->mvprint_multiline_str(0, 1, "[ENTER] to advance execution    [Q] to interrupt execution");
        control_hint_win->refresh_();

        send_typed_texts_to_gamelevel();

        success = (*game_sequence->get_current_level())->attempt(
                (*(game_sequence->get_current_level()))->attempts.begin() + (current_field - typing_field.begin()),
                vm_callback,
                gl_callback,
                vm_output_attempt_callback,
                vm_output_solution_callback);
        vm_memory_win->erase();
        vm_memory_win->refresh_();
    } catch (const UserInterrupt &e)
    {
        success = false;
    } catch (const VirtualMachineException &e)
    {
        //log2 << e.what() << endl;
        string msg(e.what());
        vm_message_win->push_message("Error : " + msg);
        vm_message_win->refresh_();
        vm_message_win->getch_();
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
    play_level();
}

void GameTUI::play()
{
    initscr_();
    try
    {
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
        init_pair(2, COLOR_BLACK, COLOR_YELLOW);
        curs_set(0);
        Window starting_screen(stdscr_->get_height(), stdscr_->get_width(), 0, 0);
        starting_screen.printstr_in_middle("Welcome to A Stressful Machine. Press any key to start the game...");
        starting_screen.refresh_();
        starting_screen.getch_();
        pick_saves();
        pick_level();
        play_level();
    } catch (...)
    {
        endwin_();
        rethrow_exception(current_exception());
    }
    endwin_();
}

void GameTUI::send_typed_texts_to_gamelevel()
{
    vector<string> texts;
    for (auto f : typing_field)
    {
        texts.push_back(f->get_typed_text());
    }

    (*(game_sequence->get_current_level()))->attempts = texts;
}

void GameTUI::get_attempts_from_gamelevel()
{
    for (int i = 0; i < typing_field.size(); i++)
    {
        typing_field[i]->set_typed_text((*(game_sequence->get_current_level()))->attempts[i]);
    }
}

