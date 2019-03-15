//
// Created by emile on 06/03/19.
//

#include <form.h>
#include <assert.h>

#include "GameTUI.h"
#include "ncurses++.h"

using namespace ncursespp;

GameTUI::GameTUI(const string &saves_dir_, const string &gamefiles_dir_) : Game(saves_dir_, gamefiles_dir_),
                                                                           typing_win(nullptr),
                                                                           instruction_win(nullptr),
                                                                           vm_input_win(nullptr),
                                                                           vm_output_win(nullptr),
                                                                           vm_memory_win(nullptr),
                                                                           vm_program_win(nullptr),
                                                                           level_picking_win(nullptr),
                                                                           save_picking_win(nullptr),
                                                                           typing_cursor_x(0),
                                                                           typing_pos_y(0)
{
    typed_text = String2D();
    typed_text.push_back("");
    typing_cursor_y = typed_text.begin();

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

    const int width = (int) size_of_longest_string(possible_saves) + 8;
    const int height = (int) possible_saves.size() + 2;
    const int starty = stdscr_->get_height() / 2 - height / 2;
    const int startx = stdscr_->get_width() / 2 - width / 2;

    if (save_picking_win == nullptr)
    {
        save_picking_win = new NcursesWindow(stdscr_->get_height(), stdscr_->get_width(), 0, 0);
        save_picking_win->printstr_centered(starty / 2, "Please pick a savefile :");
    }
    save_picking_win->refresh();

    NcursesMenu save_picking(possible_saves, height, width, starty, startx, true);

    string selected_save = possible_saves[save_picking.get_selected_item()];
    game_sequence = new GameSequence(selected_save, gamefiles_dir);

}

void GameTUI::pick_level()
{
    vector<string> possible_levels = game_sequence->get_available_levels();

    const int width = (int) size_of_longest_string(possible_levels) + 8;
    const int height = (int) possible_levels.size() + 2;
    const int starty = stdscr_->get_height() / 2 - height / 2;
    const int startx = stdscr_->get_width() / 2 - width / 2;

    if (level_picking_win == nullptr)
    {
        level_picking_win = new NcursesWindow(stdscr_->get_height(), stdscr_->get_width(), 0, 0);
        level_picking_win->printstr_centered(starty / 2, "Please pick a level :");
    }
    level_picking_win->refresh();


    NcursesMenu level_picking(possible_levels, height, width, starty, startx, true);

    game_sequence->select_level(possible_levels[level_picking.get_selected_item()]);
}

void GameTUI::play_level()
{
    const int h = stdscr_->get_height();
    const int w = stdscr_->get_width();
    typing_win = new NcursesWindow(h / 2, w / 2, 0, w / 2, true);
    typing_win->keypad_on();

    instruction_win = new NcursesWindow(h / 2, w / 2, 0, 0, true);
    fill_instructions();

    vm_input_win = new NcursesWindow(h / 2, w / 4, h / 2, 0, true);
    vm_output_win = new NcursesWindow(h / 2, w / 4, h / 2, w / 4, true);

    vm_program_win = new NcursesWindow(h / 4, w / 2, h / 2, w / 2, true);
    vm_memory_win = new NcursesWindow(h / 4, w / 2, h / 2 + h / 4, w / 2, true);

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
    instruction_win->mvprintstr(1, 2, game_sequence->get_current_level()->get_instructions());
}

void GameTUI::handle_typing()
{
    /* char *(FIELD *field, int buffer_index); */
    curs_set(1);
    int ch;
    while ((ch = typing_win->getch_()) != KEY_F(5))
    {
        switch (ch)
        {
            case KEY_RIGHT:
                if (typing_cursor_x < (*typing_cursor_y).size())
                {
                    typing_cursor_x++;
                } else if (typing_cursor_y != --typed_text.end())
                {
                    typing_cursor_y++;
                    typing_pos_y++;
                    typing_cursor_x = 0;
                }
                break;

            case KEY_LEFT:
                if (typing_cursor_x > 0)
                {
                    typing_cursor_x--;
                } else if (typing_cursor_y != typed_text.begin())
                {
                    typing_cursor_y--;
                    typing_pos_y--;
                    typing_cursor_x = (*typing_cursor_y).size();
                }
                break;

            case KEY_BACKSPACE:
                if (typing_cursor_x != 0)
                {
                    (*typing_cursor_y).erase(typing_cursor_x - 1, 1);
                    typing_cursor_x--;
                } else if (typing_cursor_y != typed_text.begin() &&
                           (*typing_cursor_y).size() + (*(--typing_cursor_y)).size() < typing_win->get_width() - 4)
                {
                    auto eraser = ++typing_cursor_y;
                    typing_cursor_y--;
                    typing_pos_y--;
                    string buff = (*eraser);
                    typed_text.erase(eraser);
                    (*typing_cursor_y) += buff;

                }
                break;

            case KEY_DC:
                if (typing_cursor_x != (*typing_cursor_y).size())
                {
                    (*typing_cursor_y).erase(typing_cursor_x, 1);
                } // Todo : add an else if clause here for multiline support
                break;

            case '\n':
                if (typed_text.size() < typing_win->get_height() - 4)
                {
                    typing_cursor_y++;
                    typed_text.insert(typing_cursor_y, "");
                    typing_cursor_y--;
                    typing_pos_y++;
                    typing_cursor_x = 0;
                }
                break;

            default:
                if (isprint(ch) && typing_cursor_x < typing_win->get_width() - 4)
                {
                    //if (cursor_x - typed_text.begin() > 15) getch();

                    //if (cursor_x - typed_text.begin() >= typed_text.capacity()) typed_text.resize(typed_text.capacity() * 2);
                    (*typing_cursor_y).insert((*typing_cursor_y).begin() + typing_cursor_x, (char) ch);

                    //if (cursor_x - typed_text.begin() > 15) getch();
                    typing_cursor_x++;
                }
                break;

        }
        typing_win->move_cursor(2, 2);
        typing_win->clear();
        typing_win->mvprintstr(2, 2, string(typed_text), 1);
        typing_win->refresh();
        typing_win->move_cursor((int) (2 + typing_pos_y), (int) (2 + (typing_cursor_x)));


    }
    curs_set(0);
    bool b = false;
    try
    {
        vm_callback = bind2nd(function<void(VirtualMachine *, GameTUI *)>(raw_vm_callback), this);
        gl_callback = bind2nd(function<void(GameLevel *, GameTUI *)>(raw_gl_callback), this);
        b = game_sequence->get_current_level()->attempt(string(typed_text), vm_callback, gl_callback);
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
            break;
        case 1:
            pick_level();
            break;
    }

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
    init_pair(1, COLOR_WHITE, COLOR_GREEN);
    curs_set(0);
    NcursesWindow starting_screen(stdscr_->get_height(), stdscr_->get_width(), 0, 0);
    starting_screen.printstr_in_middle("Welcome to A Stressful Machine. Press any key to start the game...");
    starting_screen.refresh();
    starting_screen.getch_();
    pick_saves();
    pick_level();
    play_level();
    endwin_();
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
