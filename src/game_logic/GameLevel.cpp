//
// Created by emile on 04/03/19.
//

#include <filesystem>
#include "GameLevel.h"

using namespace std;
namespace fs = filesystem;

GameLevel::GameLevel(fs::path gamefiles_dir_, string level_name_, vector<string> attempts_, VirtualMachine *vm_attempt_)
        :
        gamefiles_dir(move(gamefiles_dir_)),
        level_name(move(level_name_)),
        attempts(move(attempts_)),
        vm_attempt(vm_attempt_)
{
    solution = file_to_string(gamefiles_dir / "levels" / level_name / "solution");
    instructions = file_to_string(gamefiles_dir / "levels" / level_name / "instructions");
    input = ifstream(gamefiles_dir / "levels" / level_name / "input");
    vm_sol = nullptr;
    if (attempts.empty())
    {
        attempts.emplace_back("");
    }
    current_attempt = attempts.begin();
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

    vm_attempt = new VirtualMachine(*current_attempt, &input_line, &attempt_ostream,
                                    {gamefiles_dir / "levels" / level_name / "lib"});
    vm_attempt->set_output_callback(vm_output_attempt_callback);

    try
    {
        vm_sol = new VirtualMachine(solution, &input_line, &solution_ostream,
                                    {gamefiles_dir / "levels" / level_name / "lib"});
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
        reset_input();
        throw e;
    }

    input_line.clear();
    input_line.seekg(0);

    try
    {
        vm_sol->loop();
    } catch (VirtualMachineException &e)
    {
        throw runtime_error(string("Solution looping throw exception : ") + string(e.what()));
    }


    bool r = (attempt_ostream.str() == solution_ostream.str());
    return r;
}

bool GameLevel::attempt(const string &program_,
                        const function<void(VirtualMachine *)> &vm_callback,
                        const function<void(GameLevel *)> &gl_callback,
                        const function<void(int)> &vm_output_attempt_callback,
                        const function<void(int)> &vm_output_solution_callback)
{
    *current_attempt = program_;
    reset_input();
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

bool GameLevel::attempt(vector<string>::iterator current_attempt_,
                        const function<void(VirtualMachine *)> &vm_callback,
                        const function<void(GameLevel *)> &gl_callback,
                        const function<void(int)> &vm_output_attempt_callback,
                        const function<void(int)> &vm_output_solution_callback)
{
    current_attempt = current_attempt_;
    reset_input();
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

string GameLevel::get_level_name()
{
    return level_name;
}

