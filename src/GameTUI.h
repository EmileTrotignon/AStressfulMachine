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
#include "VirtualMachineTUI.h"

class GameTUI : public Game
{
private:

    WINDOW *typing_win;
    WINDOW *instruction_win;
    WINDOW *vm_input_win;
    WINDOW *vm_output_win;
    WINDOW *vm_memory_win;
    WINDOW *vm_program_win;
    function<void(VirtualMachine *)> looper;
    string typed_text;


    void pick_saves();

    void pick_level();

    void play_level();

    void fill_instructions();

    void initialize_typing_win();

    void handle_typing();

public:
    GameTUI(const string &saves_dir, const string &gamefiles_dir);

    void play() override;

    friend void vm_looper(VirtualMachine *vm, GameTUI *gi);

    friend VirtualMachineTUI;
};

void vm_looper(VirtualMachine *vm, GameTUI *gi);

class Looper : public binary_function<VirtualMachine *, GameTUI *, void>
{
public:
    void operator()(VirtualMachine *vm, GameTUI *gt);

};

#endif //A_STRESSFUL_MACHINE_GAMETUI_H
