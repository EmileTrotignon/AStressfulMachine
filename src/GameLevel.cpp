//
// Created by emile on 04/03/19.
//

#include "GameLevel.h"

using namespace std;

GameLevel::GameLevel(const string &gamefiles_dir_, const string &level_name_, VirtualMachine *vm_attempt_)
        : gamefiles_dir(gamefiles_dir_),
          level_name(level_name_), vm_attempt(vm_attempt_)
{
    solution = file_to_string(gamefiles_dir + "/levels/" + level_name + "/solution");
    instructions = file_to_string(gamefiles_dir + "/levels/" + level_name + "/instructions");
    input = ifstream(gamefiles_dir + "/levels/" + level_name + "/input");
    vm_sol = nullptr;
    program_attempt = "";
}

void GameLevel::reset_input(streamoff pos)
{
    input.clear();
    input.seekg(pos);
}

bool GameLevel::attempt_one_input(const function<void(VirtualMachine *)> &vm_callback)
{
    ostringstream output_attempt;
    ostringstream output_sol;
    string input_line_str;

    getline(input, input_line_str);
    istringstream input_line(input_line_str);

    vm_attempt = new VirtualMachine(program_attempt, &input_line, &output_attempt);

    vm_sol = new VirtualMachine(solution, &input_line, &output_sol);
    vm_sol->loop();

    input_line.clear();
    input_line.seekg(0);

    vm_attempt->loop(vm_callback);

    return (output_attempt.str() == output_sol.str());
}

bool GameLevel::attempt(const string &program_, const function<void(VirtualMachine *)> &vm_callback,
                        const function<void(GameLevel *)> &gl_callback)
{
    program_attempt = program_;

    while(!input.eof())
    {
        if (gl_callback != nullptr) gl_callback(this);
        if (!attempt_one_input(vm_callback)) return false;
    }
    reset_input();
    return true;
}

string GameLevel::get_instructions()
{
    return instructions;
}

ifstream &GameLevel::get_input()
{
    return input;
}

string GameLevel::get_input_as_string()
{
    streamoff pos = input.tellg();
    string in((istreambuf_iterator<char>(input)), istreambuf_iterator<char>());
    reset_input(pos);
    return in;
}