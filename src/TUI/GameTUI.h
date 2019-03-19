//
// Created by emile on 06/03/19.
//

#ifndef A_STRESSFUL_MACHINE_GAMETUI_H
#define A_STRESSFUL_MACHINE_GAMETUI_H

#include <ncurses.h>
#include <form.h>
#include <menu.h>
#include <functional>

#include "Game.h"
#include "ncurses++.h"

using namespace ncursespp;

class GameTUI : public Game
{
private:

    Window *typing_win;
    Window *instruction_win;
    Window *vm_input_win;
    Window *vm_output_win;
    Window *vm_memory_win;
    Window *vm_program_win;
    Window *level_picking_win;
    Window *save_picking_win;
    Window *success_menu_win;
    Field *typing_field;

    int n_lines_sol_output;
    int n_lines_attempt_output;


    void pick_saves();

    void pick_level();

    void play_level();

    void fill_instructions();

    void handle_typing();

    void handle_success();

    void handle_failure();

public:

    GameTUI(const string &saves_dir, const string &gamefiles_dir);

    ~GameTUI();

    void play() override;

    friend void raw_vm_callback(VirtualMachine *, GameTUI *, bool);

    friend void raw_gl_callback(GameLevel *, GameTUI *, bool);

    friend void raw_vm_solution_out_callback(int output, GameTUI *gi);

    friend void raw_vm_attempt_out_callback(int output, GameTUI *gi);



};

#endif //A_STRESSFUL_MACHINE_GAMETUI_H
