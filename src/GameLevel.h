//
// Created by emile on 04/03/19.
//

#ifndef ASTRESSFULMACHINE_GAMELEVEL_H
#define ASTRESSFULMACHINE_GAMELEVEL_H

#include <fstream>
#include <functional>
#include "VirtualMachine.h"
#include "utilities.h"

/*#define LEVELFILES_FOLDER "data/gamefiles/levels"*/

/**
 * This class enable the player to complete a level.
 */

class WINDOW;

class GameLevel
{
private:
    string gamefiles_dir;
    string level_name;
    string solution;
    string instructions;
    string program_attempt;

    VirtualMachine *vm_sol;
    VirtualMachine *vm_attempt;


public:

    ifstream input;

    /**
     * Basic constructor that uses the level name to open the correct file.
     * @param level_name The name of the level (it is the directory, you cannot put anything here)
     */
    explicit GameLevel(const string &gamefiles_dir, const string &level_name, VirtualMachine *vm_attempt = nullptr);

    /**
     * Reset the input to it's just opened state.
     */
    void reset_input();

    /**
     * Check if the line of the input results in the same output for the attempt and the solution.
     * @param verbose_level
     * @return
     */
    bool attempt_one_input(const function<void(VirtualMachine *)> &vm_looper);

    bool attempt(const string &program, const function<void(VirtualMachine *)> &vm_callback = nullptr,
                 const function<void(GameLevel *)> &gm_callback = nullptr);

    string get_instructions();

    const ifstream &get_input();

    friend void print_input_to_win(WINDOW *win, GameLevel *gl);


};


#endif //ASTRESSFULMACHINE_GAMELEVEL_H
