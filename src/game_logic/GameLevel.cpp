//
// Created by emile on 04/03/19.
//

#include "GameLevel.h"

using namespace std;

GameLevel::GameLevel(const string &gamefiles_dir_, const string &level_name_, ostringstream *solution_output_stream_,
                     ostringstream *attempt_output_stream_, VirtualMachine *vm_attempt_) :
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

bool GameLevel::attempt_one_input(const function<void(VirtualMachine *)> &vm_callback, ostringstream *attempt_ostream,
                                  ostringstream *solution_ostream)
{

    string input_line_str;
    bool allocated_sos = false;
    bool allocated_aos = false;
    if (solution_ostream == nullptr)
    {
        solution_ostream = new ostringstream;
        allocated_sos = true;
    }

    if (attempt_ostream == nullptr)
    {
        attempt_ostream = new ostringstream;
        allocated_aos = true;
    }

    getline(input, input_line_str);
    istringstream input_line(input_line_str);

    vm_attempt = new VirtualMachine(program_attempt, &input_line, attempt_ostream);

    vm_sol = new VirtualMachine(solution, &input_line, solution_ostream);
    vm_sol->loop();

    input_line.clear();
    input_line.seekg(0);

    vm_attempt->loop(vm_callback);

    bool r = (attempt_ostream->str() == solution_ostream->str());
    if (allocated_aos) delete attempt_ostream;
    if (allocated_sos) delete solution_ostream;
    return r;
}

bool GameLevel::attempt(const string &program_, const function<void(VirtualMachine *)> &vm_callback,
                        const function<void(GameLevel *)> &gl_callback, ostringstream *attempt_ostream,
                        ostringstream *solution_ostream)
{

    bool allocated_sos = false;
    bool allocated_aos = false;
    program_attempt = program_;
    if (solution_ostream == nullptr)
    {
        solution_ostream = new ostringstream;
        allocated_sos = true;
    }

    if (attempt_ostream == nullptr)
    {
        attempt_ostream = new ostringstream;
        allocated_aos = true;
    }
    while (!input.eof())
    {
        if (gl_callback != nullptr) gl_callback(this);
        if (!attempt_one_input(vm_callback, attempt_ostream, solution_ostream))
        {
            if (allocated_aos) delete attempt_ostream;
            if (allocated_sos) delete solution_ostream;
            return false;
        }
    }
    reset_input();
    if (allocated_aos) delete attempt_ostream;
    if (allocated_sos) delete solution_ostream;
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