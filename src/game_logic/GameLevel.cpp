//
// Created by emile on 04/03/19.
//

#include "GameLevel.h"

using namespace std;

//ofstream log("log");

GameLevel::GameLevel(const string &gamefiles_dir_, const string &level_name_, VirtualMachine *vm_attempt_) :
        gamefiles_dir(gamefiles_dir_),
        level_name(level_name_),
        vm_attempt(vm_attempt_)
{
    solution = file_to_string(gamefiles_dir + "/levels/" + level_name + "/solution");
    instructions = file_to_string(gamefiles_dir + "/levels/" + level_name + "/instructions");
    input = ifstream(gamefiles_dir + "/levels/" + level_name + "/input");
    vm_sol = nullptr;
    program_attempt = "";
}

GameLevel::~GameLevel()
{
    delete vm_attempt;
    delete vm_sol;
    input.close();
}

void GameLevel::reset_input(streamoff pos)
{
    input.clear();
    input.seekg(pos);
}

bool GameLevel::attempt_one_input(const function<void(VirtualMachine *)> &vm_callback,
                                  const function<void(int)> &vm_output_attempt_callback,
                                  const function<void(int)> &vm_output_solution_callback)
{

    string input_line_str;

    ostringstream solution_ostream;
    ostringstream attempt_ostream;

    getline(input, input_line_str);
    //  replace(input_line_str.begin(), input_line_str.end(), ' ', '\n');
    istringstream input_line(input_line_str);

    vm_attempt = new VirtualMachine(program_attempt, &input_line, &attempt_ostream);
    vm_attempt->set_output_callback(vm_output_attempt_callback);

    try
    {
        vm_sol = new VirtualMachine(solution, &input_line, &solution_ostream);
    } catch (const VirtualMachineException &e)
    {
        throw runtime_error(string("Solution initialisation throw exception : ") + string(e.what()));
    }
    vm_sol->set_output_callback(vm_output_solution_callback);
    try
    {
        vm_attempt->loop(vm_callback);

    } catch (const VirtualMachineException &e)
    {
        input_line.clear();
        input_line.seekg(0);
        throw e;
    }

    input_line.clear();
    input_line.seekg(0);

    vm_sol->loop();

    bool r = (attempt_ostream.str() == solution_ostream.str());
    return r;
}

bool GameLevel::attempt(const string &program_,
                        const function<void(VirtualMachine *)> &vm_callback,
                        const function<void(GameLevel *)> &gl_callback,
                        const function<void(int)> &vm_output_attempt_callback,
                        const function<void(int)> &vm_output_solution_callback)
{
    program_attempt = program_;
    while (!input.eof())
    {
        if (gl_callback != nullptr) gl_callback(this);
        if (!attempt_one_input(vm_callback, vm_output_attempt_callback, vm_output_solution_callback))
        {
            reset_input();
            return false;
        }
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