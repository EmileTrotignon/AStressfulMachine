//
// Created by emile on 04/03/19.
//

#include "GameLevel.h"

using namespace std;

GameLevel::GameLevel(const string &ln)
{
    level_name = ln;
    solution = file_to_string(LEVELFILES_FOLDER "/" + level_name + "/solution");
    instructions = file_to_string(LEVELFILES_FOLDER "/" + level_name + "/instructions");
    input = ifstream(LEVELFILES_FOLDER "/" + level_name + "/input");
    vm_attempt = nullptr;
    vm_sol = nullptr;
    program_attempt = "";
}

void GameLevel::reset_input()
{
    input.clear();
    input.seekg(0);
}

bool GameLevel::attempt_one_input(int verbose_level)
{
    ostringstream output_attempt;
    ostringstream output_sol;
    string input_str;

    getline(input, input_str);
    istringstream whole_input(input_str);

    vm_attempt = new VirtualMachine(program_attempt, &whole_input, &output_attempt);
    if (verbose_level >= 1) vm_attempt->be_verbose();
    if (verbose_level >= 2) vm_attempt->be_verbose_procedure();

    vm_sol = new VirtualMachine(solution, &whole_input, &output_sol);
    vm_sol->loop();

    whole_input.clear();
    whole_input.seekg(0);

    vm_attempt->loop();

    return (output_attempt.str() == output_sol.str());
}

bool GameLevel::attempt(const string &program, int verbose_level)
{


    while(!input.eof())
    {
        if (!attempt_one_input(verbose_level)) return false;
    }
    reset_input();
    return true;
}

void GameLevel::play_sequence()
{
    cout << "What do you want to do ?"
            "\nAttempt to solve [A]; Attempt in verbose mode [V]; Quit [Q]" << endl;
    string code;
    cin >> code;
    if (code == "A" || code == "a" || code == "V" || code == "v")
    {
        string program;
        cin >> program;
        bool success;
        if (code == "V" || code == "v") success = attempt(program, 1);
        else success = attempt(program);
        if (success)
        {
            cout << "Great job" << endl;
        } else
        {
            cout << "Oh no you were defeated :(" << endl;
            play_sequence();
        }
    } else if (code == "Q" || code == "q")
    {
        cout << "See you later :)" << endl;
    } else
    {
        cout << "Please input one of the code" << endl;
        play_sequence();
    }
}

void GameLevel::tui_play()
{
    cout << instructions << endl;
    play_sequence();

}