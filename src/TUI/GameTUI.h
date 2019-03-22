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

    Window *control_hint_win;
    Window *typing_win;
    Window *instruction_win;
    Window *vm_input_win;
    Window *vm_output_win;
    Window *vm_memory_win;
    Window *vm_output_solution_win;
    Window *vm_output_attempt_win;
    MessageStack *vm_message_win;
    Window *level_picking_win;
    Window *save_picking_win;
    Window *success_menu_win;
    array<Field *, 5> typing_field;
    array<Field *, 5>::iterator current_field;

    int n_lines_sol_output;
    int n_lines_attempt_output;

    void fill_instructions();

    void draw_title();

    void pick_saves();

    void pick_level();

    void play_level();

    void handle_typing();

    void handle_success();

    void handle_failure();

    void send_typed_texts_to_gamelevel();

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
