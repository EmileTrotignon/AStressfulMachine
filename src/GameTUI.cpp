//
// Created by emile on 06/03/19.
//

#include <form.h>
#include <assert.h>

#include "GameTUI.h"
#include "ncurses++.h"

using namespace ncursespp;

GameTUI::GameTUI(const string &saves_dir_, const string &gamefiles_dir_) : Game(saves_dir_, gamefiles_dir_)
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
    init_pair(1, COLOR_WHITE, COLOR_GREEN);
    curs_set(0);

    const int h = stdscr_->get_height();
    const int w = stdscr_->get_width();

    typing_win = Window(h / 2, w / 2, 0, w / 2, true);
    typing_field = Field(KEY_F(5), typing_win.get_height() - 4, typing_win.get_width() - 4, typing_win.get_starty() + 2,
                         typing_win.get_startx() + 2);

    vm_input_win = Window(h / 2, w / 4, h / 2, 0, true);
    vm_output_win = Window(h / 2, w / 4, h / 2, w / 4, true);

    vm_program_win = Window(h / 4, w / 2, h / 2, w / 2, true);
    vm_memory_win = Window(h / 4, w / 2, h / 2 + h / 4, w / 2, true);

}

void GameTUI::pick_saves()
{
    vector<string> possible_saves = save_picker->get_saves();

    Window save_picking_win(stdscr_->get_height(), stdscr_->get_width(), 0, 0);

    Menu save_picking(possible_saves, save_picking_win, "Please pick a savefile :");

    string selected_save = possible_saves[save_picking.select_item()];
    game_sequence = new GameSequence(selected_save, gamefiles_dir);

}

void GameTUI::pick_level()
{
    vector<string> possible_levels = game_sequence->get_available_levels();

    Window level_picking_win(stdscr_->get_height(), stdscr_->get_width(), 0, 0);


    Menu level_picking(possible_levels, level_picking_win, "Please pick a level :");
    game_sequence->select_level(possible_levels[level_picking.select_item()]);

    //  typing_win.clear();
    typing_field = Field(KEY_F(5), typing_win.get_height() - 4, typing_win.get_width() - 4, typing_win.get_starty() + 2,
                         typing_win.get_startx() + 2);;
    //instruction_win.clear();
    //vm_input_win.clear();
    //vm_output_win.clear();

    //vm_program_win.clear();
    //vm_memory_win.clear();
    fill_instructions();


}

void GameTUI::play_level()
{

    typing_win.refresh_();
    typing_field.refresh_();
    instruction_win.refresh_();
    vm_input_win.refresh_();
    vm_output_win.refresh_();
    vm_memory_win.refresh_();
    vm_program_win.refresh_();
    typing_win.move_cursor(2, 2);
    handle_typing();
}

void GameTUI::fill_instructions()
{
    instruction_win.mvprintstr(1, 2, game_sequence->get_current_level()->get_instructions());
}

void GameTUI::handle_typing()
{
    //getch();
    typing_field.type();
    bool b = false;
    try
    {
        vm_callback = bind2nd(function<void(VirtualMachine *, GameTUI *)>(raw_vm_callback), this);
        gl_callback = bind2nd(function<void(GameLevel *, GameTUI *)>(raw_gl_callback), this);
        b = game_sequence->get_current_level()->attempt(typing_field.get_typed_text(), vm_callback, gl_callback);
    } catch (const VirtualMachineException &e)
    {
        b = false;
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

    Window success_menu_win = Window(stdscr_->get_height(), stdscr_->get_width(), 0, 0);

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

void GameTUI::play()
{

    Window starting_screen(stdscr_->get_height(), stdscr_->get_width(), 0, 0);
    starting_screen.printstr_in_middle("Welcome to A Stressful Machine. Press any key to start the game...");
    starting_screen.refresh_();
    starting_screen.getch_();
    pick_saves();
    pick_level();
    play_level();
    endwin_();
}

void print_memory_to_win(Window &win, VirtualMachine *vm)
{
    win.clear();
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
    win.clear();
    win.mvprintstr(2, 2, gl->get_input_as_string());
    win.refresh_();
}


void raw_vm_callback(VirtualMachine *vm, GameTUI *gi)
{
    print_memory_to_win(gi->vm_memory_win, vm);
    gi->typing_field.attron_char(vm->get_current_operator() - vm->get_program().begin(), COLOR_PAIR(1));
    gi->typing_win.refresh_();
    gi->typing_field.refresh_();
    gi->vm_memory_win.getch_();
}

void raw_gl_callback(GameLevel *gl, GameTUI *gi)
{
    print_input_to_win(gi->vm_input_win, gl);
    //gi->vm_input_win->getch_();
}


