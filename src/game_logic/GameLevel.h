//
// Created by emile on 04/03/19.
//

#ifndef ASTRESSFULMACHINE_GAMELEVEL_H
#define ASTRESSFULMACHINE_GAMELEVEL_H

#include <iostream>
#include <fstream>
#include <functional>
#include <filesystem>
#include "../virtual_machine/VirtualMachine.h"
#include "../file_utilities/file_utilities.h"

/*#define LEVELFILES_FOLDER "data/gamefiles/levels"*/


/**
 * This class enables the player to complete a level.
 */

namespace fs = filesystem;

class GameLevel
{
private:
    fs::path gamefiles_dir;
    ifstream input;
    string level_name;
    string solution;
    string instructions;
    vector<string>::iterator current_attempt;

    VirtualMachine *vm_sol;
    VirtualMachine *vm_attempt;


public:

    /**
     * Basic constructor that uses the level name to open the correct file.
     * @param level_name The name of the level (it is the directory, you cannot put anything here)
     */
    GameLevel(fs::path gamefiles_dir, string level_name, vector<string> attempts = {},
              VirtualMachine *vm_attempt = nullptr);

    ~GameLevel();

    /**
     * Reset the input to it's just opened state.
     */
    void reset_input(streamoff pos = 0);

    /**
     * Check if the line of the input results in the same output for the attempt and the solution.
     * @param verbose_level
     * @return
     */
    bool attempt_one_input(const function<void(VirtualMachine *)> &vm_callback,
                           const function<void(int)> &vm_output_attempt_callback,
                           const function<void(int)> &vm_output_solution_callback);

    bool attempt(const string &program_,
                 const function<void(VirtualMachine *)> &vm_callback = nullptr,
                 const function<void(GameLevel *)> &gl_callback = nullptr,
                 const function<void(int)> &vm_output_attempt_callback = nullptr,
                 const function<void(int)> &vm_output_solution_callback = nullptr);

    bool attempt(vector<string>::iterator current_attempts,
                 const function<void(VirtualMachine *)> &vm_callback = nullptr,
                 const function<void(GameLevel *)> &gl_callback = nullptr,
                 const function<void(int)> &vm_output_attempt_callback = nullptr,
                 const function<void(int)> &vm_output_solution_callback = nullptr);

    string get_instructions();

    ifstream &get_input();

    string get_input_as_string();

    vector<string> attempts;

    string get_level_name();

    //friend void print_input_to_win(WINDOW *win, GameLevel *gl);


};


#endif //ASTRESSFULMACHINE_GAMELEVEL_H
