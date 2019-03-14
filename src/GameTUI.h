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
#include "NcursesWindow.h";

class GameTUI : public Game
{
private:

    NcursesWindow *typing_win;
    NcursesWindow *instruction_win;
    NcursesWindow *vm_input_win;
    NcursesWindow *vm_output_win;
    NcursesWindow *vm_memory_win;
    NcursesWindow *vm_program_win;
    function<void(VirtualMachine *)> vm_callback;
    function<void(GameLevel *)> gl_callback;
    string typed_text;


    void pick_saves();

    void pick_level();

    void play_level();

    void fill_instructions();

    void initialize_typing_win();

    void handle_typing();

public:

    GameTUI(const string &saves_dir, const string &gamefiles_dir);

    ~GameTUI();

    void play() override;

    friend void raw_vm_callback(VirtualMachine *vm, GameTUI *gi);

    friend void raw_gl_callback(GameLevel *gl, GameTUI *gi);

};

void raw_vm_callback(VirtualMachine *vm, GameTUI *gi);

void raw_gl_callback(GameLevel *gl, GameTUI *gi);

#endif //A_STRESSFUL_MACHINE_GAMETUI_H
