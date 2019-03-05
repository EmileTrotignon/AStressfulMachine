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
}

bool GameLevel::attempt(const string &program, int verbose_level)
{


    while(!input.eof())
    {
        ostringstream output_attempt;
        ostringstream output_sol;
        string input_str;
        getline(input, input_str);
        istringstream whole_input(input_str);
        VirtualMachine vm_attempt(program, &whole_input, &output_attempt);
        if (verbose_level >= 1) vm_attempt.be_verbose();
        if (verbose_level >= 2) vm_attempt.be_verbose_procedure();
        VirtualMachine vm_sol(solution, &whole_input, &output_sol);
        vm_sol.loop();
        whole_input.clear();
        whole_input.seekg(0);
        vm_attempt.loop();
        if (output_attempt.str() != output_sol.str())
        {
            cout << "The outputs differs :"
                    "\n Input: " << input_str
                 << "\n Attempt output: " << output_attempt.str()
                 << "\n Expected output: " << output_sol.str() << endl;
            input.clear();
            input.seekg(0);
            return false;
        }
        input_str = "";
    }
    input.clear();
    input.seekg(0);
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

void GameLevel::play()
{
    cout << instructions << endl;
    play_sequence();

}