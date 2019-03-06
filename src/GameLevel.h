//
// Created by emile on 04/03/19.
//

#ifndef ASTRESSFULMACHINE_GAMELEVEL_H
#define ASTRESSFULMACHINE_GAMELEVEL_H

#include <fstream>
#include "VirtualMachine.h"
#include "utilities.h"

#define LEVELFILES_FOLDER "data/gamefiles/levels"

/**
 * This class enable the player to complete a level.
 */
class GameLevel
{
private:
    string level_name;
    string solution;
    string instructions;
    string program_attempt;
    ifstream input;

    VirtualMachine *vm_sol;
    VirtualMachine *vm_attempt;


    void play_sequence();

public:
    /**
     * Basic constructor that uses the level name to open the correct file.
     * @param level_name The name of the level (it is the directory, you cannot put anything here)
     */
    explicit GameLevel(const string &level_name);

    /**
     * Reset the input to it's just opened state.
     */
    void reset_input();

    /**
     * Set up the level for a step by step attempt to solve.
     * @param program The program of the attempt.
     */
    void initialise_step_by_step_attempt(const string &program);

    /**
     * Do one step of the step by step attempt.
     * One step is one iteration of the VM.
     */
    void do_one_step();

    /**
     * Check if the line of the input results in the same output for the attempt and the solution.
     * @param verbose_level
     * @return
     */
    bool attempt_one_input(int verbose_level);

    bool attempt(const string &program, int verbose_level = 0);


    void tui_play();
};


#endif //ASTRESSFULMACHINE_GAMELEVEL_H
