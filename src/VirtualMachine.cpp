//
// Created by emile on 25/02/19.
//

#include <fstream>
#include <assert.h>
#include "VirtualMachine.h"
#include "VirtualMachineProcedure.h"

VirtualMachine::VirtualMachine(const string &p, istream *i, ostream *o, size_t s, int *m)
{
    status = PAUSED;
    program = p;
    in = i;
    out = o;
    size = s;
    memory = m;
    if (program[0] == FILE_MARKER) program = file_to_string(program.substr(1));
    if (isdigit(program[0]))
    {
        size_t t;
        size = (size_t) extract_number_from_program(0, &t);
        program = program.substr(t);
    }
    if (m == nullptr) memory = new int[size]{0};
    memory_ptr = memory;
    current_operator = 0;
    procedure_call = nullptr;
    verbose = false;
    verbose_procedure = false;
    depth = 0;
    initialize_anchor_map();
}

VirtualMachine::~VirtualMachine()
{
    delete[] memory;
    delete procedure_call;
}

void VirtualMachine::initialize_anchor_map()
{
    while (current_operator < program.size())
    {
        if (program[current_operator] == OPEN_GOTO && program[current_operator + 1] != GOTO_MARKER)
        {
            current_operator++;
            size_t t;
            int anchor = extract_number_from_program(current_operator, &t);
            if (status == ERROR) return;
            anchor_map[anchor] = (int) t + current_operator;
        }
        current_operator++;
    }
    current_operator = 0;
}

void VirtualMachine::ptr_incr()
{
    memory_ptr++;
}

void VirtualMachine::ptr_dincr()
{
    memory_ptr--;
}

void VirtualMachine::val_incr()
{
    (*memory_ptr)++;
}

void VirtualMachine::val_dincr()
{
    (*memory_ptr)--;
}

void VirtualMachine::val_out()
{
    if (procedure_call == nullptr)
    {
        *out << *memory_ptr;
    } else
    {
        if (procedure_call->status == INPUTTING)
        {
            procedure_call->input(*memory_ptr);
        } else
        {
            *out << *memory_ptr;
        }
    }
}


void VirtualMachine::char_out()
{
    *out << (char) *memory_ptr;
}

void VirtualMachine::val_in()
{
    if (procedure_call == nullptr)
    {
        *in >> *memory_ptr;
    } else
    {
        if (procedure_call->status == OUTPUTTING)
        {
            *memory_ptr = procedure_call->output;
        } else
        {
            if (procedure_call->status == INPUTTING)
                error(PROC_ASK_OUTPUT_WITHOUT_INPUT);
            else if (procedure_call->status == PAUSED)
                error(PROC_ASK_OUPUT_WHEN_FINISHED);
        }
    }
}

void VirtualMachine::handle_bracket()
{
    current_operator++;
    switch (program[current_operator])
    {
        case GOTO_MARKER:
            current_operator++;
            go_to_cond();
            break;
        default:
            exit_goto();
            return;
    }
}

void VirtualMachine::go_to_cond()
{
    if (program[current_operator] == COND_EQUAL)
    {
        if (*memory_ptr == 0)
        {
            current_operator++;
            go_to();
            return;
        } else exit_goto();
    } else if (program[current_operator] == COND_GREATER)
    {
        if (*memory_ptr > 0)
        {
            current_operator++;
            go_to();
            return;
        } else exit_goto();
    } else if (program[current_operator] == COND_DIFF)
    {
        if (*memory_ptr != 0)
        {
            current_operator++;
            go_to();
            return;
        } else exit_goto();
    } else if (program[current_operator] == COND_LESSER)
    {
        if (*memory_ptr < 0)
        {
            current_operator++;
            go_to();
            return;
        } else exit_goto();
    } else
    {
        go_to();
        return;
    }
}

void VirtualMachine::go_to()
{
    int anchor = extract_number_from_program(current_operator); //stoi(program.substr(current_operator, string::npos));
    go_to_anchor(anchor);
}

void VirtualMachine::go_to_anchor(int anchor)
{
    current_operator = anchor_map[anchor];
}

void VirtualMachine::exit_goto()
{
    int i = corresponding_par(program, OPEN_GOTO, CLOSE_GOTO, current_operator - 1);
    if (i == -1)
    {
        error(UNMATCHED_OPEN_BRACKET);
        return;
    }
    current_operator = (unsigned int) i;
}

void VirtualMachine::ptr_jump()
{
    memory_ptr = memory + (*memory_ptr);
}

void VirtualMachine::ptr_reset()
{
    memory_ptr = memory;
}

void VirtualMachine::val_reset()
{
    *memory_ptr = 0;
}

void VirtualMachine::do_n_time()
{
    string number = program.substr(current_operator + 1);
    int n;
    size_t t;
    n = extract_number_from_program(current_operator + 1, &t); //stoi(number, &t);
    current_operator = (unsigned int) t + 1;
    for (int j = 0; j < n; j++)
    {
        do_one_iteration(false);
        if (status != RUNNING) return;
    }
}

void VirtualMachine::call_procedure()
{

    int i = corresponding_par(program, OPEN_PROC, CLOSE_PROC, current_operator);
    if (i == -1)
    {
        error(UNMATCHED_CURLY_BRACKET);
        return;
    }

    string procedure = program.substr(current_operator + 1, (unsigned int) i - current_operator);
    string code;
    if (i - 1 == current_operator) // If there is no filename it mean a recursive call
    {
        code = program;
    } else
    {
        current_operator = (unsigned int) i;
        if (procedure[0] == FILE_MARKER)
        {
            code = file_to_string(procedure.substr(1, procedure.size() - 2));
            if (status == ERROR) return;
        } else
        {
            code = procedure;
        }
    }
    if (verbose_procedure) message(STARTING_PROCEDURE DEPTH);
    procedure_call = new VirtualMachineProcedure(code, nullptr, nullptr, depth + 1);
    if (verbose_procedure) procedure_call->be_verbose();
    loop_procedure();
}

string VirtualMachine::file_to_string(string filename)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        error(UNABLE_TO_OPEN_FILE);
        return "";
    }
    string c((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    return c;
}

void VirtualMachine::loop_procedure()
{
    if (procedure_call == nullptr)
    {
        error(LOOP_NONEXISTING_PROC);
        return;
    }
    procedure_call->loop();
    if (procedure_call->status == PAUSED)
    {
        delete procedure_call;
        procedure_call = nullptr;
    } else if (procedure_call->status == ERROR)
    {
        error(ERROR_IN_PROC);
        return;
    }
}

void VirtualMachine::terminate_procedure()
{
    if (procedure_call == nullptr)
    {
        error(TERMINATE_NONEXISTING_PROC);
        return;
    }
    delete procedure_call;
    procedure_call = nullptr;
}

void VirtualMachine::error(int code)
{
    switch (code)
    {
        default:
            break;
        case OUT_OF_MEMORY:
            cout << "Runtime error : The VirtualMachine is out of memory.";
            break;

        case NEGATIVE_MEMORY_ACCESS:
            cout << "Runtime error : The program tried to access negative memory.";
            break;

        case UNMATCHED_OPEN_BRACKET:
            cout << "Syntax error : unmatched '" << OPEN_GOTO << "'.";
            break;

        case UNMATCHED_CLOSED_BRACKET:
            cout << "Syntax error : unmatched '" << CLOSE_GOTO << "'.";
            break;

        case UNMATCHED_CURLY_BRACKET:
            cout << "Syntax error : unmatched '" << OPEN_PROC << "'.";
            break;

        case PROC_ASK_OUTPUT_WITHOUT_INPUT:
            cout << "Procedure error: tried to access procedure output when it still needed input.";
            if (verbose_procedure) cout << endl << (string) (*procedure_call);
            else cout << " This happened at char #" << procedure_call->current_operator << "in the procedure.";
            break;

        case PROC_ASK_OUPUT_WHEN_FINISHED:
            cout << "Procedure error: tried to access procedure output its execution was finished.";
            break;

        case UNABLE_TO_OPEN_FILE:
            cout << "Runtime error: the virtual machine is unable to open a file.";
            break;

        case TERMINATE_NONEXISTING_PROC:
            cout << "Procedure error: trying to terminate a procedure that does not exist.";
            break;

        case ERROR_IN_PROC:
            cout << "Procedure error: another error occurred in the current procedure.";
            break;
        case INVALID_NUMBER:
            cout << "Syntax error : invalid number.";
            break;
    }
    if (verbose) cout << endl << (string) (*this);
    else cout << " This Happened at char #" << current_operator << endl;
    status = ERROR;
}

void VirtualMachine::do_one_iteration(bool advance)
{
    if (current_operator >= program.size())
    {
        if (verbose) message(FINISHED);
        status = PAUSED;
        return;
    }
    if (status != RUNNING) return;
    //cout << program[current_operator] << endl;
    switch (program[current_operator])
    {
        default:
            break;

        case PTR_INCR:
            // This operator make the pointer point to the cell after the current cell
            ptr_incr();
            break;

        case PTR_DINCR:
            // This operator make the pointer point to the cell before the current cell
            ptr_dincr();
            break;

        case VAL_INCR:
            // This operator increment the current value
            val_incr();
            break;

        case VAL_DINCR:
            // This operator decrement the current value
            val_dincr();
            break;

        case VAL_OUT:
            // This operator output the current value as an int
            val_out();
            break;
        case CHAR_OUT:
            // This operator output the current value as a char
            char_out();
            break;

        case VAL_IN:
            // This operator input a value into the current cell
            val_in();
            break;

        case OPEN_GOTO:
            // This operator jumps to the corresponding ']' if the current cell contains a 0
            handle_bracket();
            //if (status != 1) return;
            break;

        case PTR_JUMP:
            // This operator treats the current cell's content as a pointer and jumps to it.
            ptr_jump();
            break;

        case PTR_RESET:
            // This operator make the pointed cell the cell 0
            ptr_reset();
            break;

        case VAL_RESET:
            // This operator set the pointed cell's content to 0
            val_reset();
            break;

        case DO_N_TIME:
            // This operator's syntax is as follow : *NUMBER[OPERATOR]
            // for instance *100> will jump a 100 case to the right.
            // #*100> will set the current pointed case to be the 100th.
            do_n_time();
            break;

        case OPEN_PROC:
            call_procedure();
            break;

        case TERMINATE_PROC:
            terminate_procedure();
            break;
    }
    if (memory_ptr >= memory + size)
    {
        error(OUT_OF_MEMORY);
        return;
    }
    if (memory_ptr < memory)
    {
        error(NEGATIVE_MEMORY_ACCESS);
        return;
    }
    if (advance) current_operator++;
    if (verbose && status == RUNNING) cout << (string) (*this);

}

void VirtualMachine::loop()
{
    if (verbose)
    {
        message(LAUNCHING);
        cout << (string) (*this);
    }
    status = RUNNING;
    while (status == RUNNING)
    {
        do_one_iteration();
    }
}

size_t VirtualMachine::get_size()
{
    return size;
}

int VirtualMachine::get_current_operator()
{
    return current_operator;
}

int VirtualMachine::get_status()
{
    return status;
}

int *VirtualMachine::get_memory()
{
    return memory;
}

int *VirtualMachine::get_memory_ptr()
{
    return memory_ptr;
}

void VirtualMachine::be_verbose()
{
    verbose = true;
}

void VirtualMachine::stop_verbose()
{
    verbose = false;
    verbose_procedure = false;
}

void VirtualMachine::be_verbose_procedure()
{
    verbose = true;
    verbose_procedure = true;
}

void VirtualMachine::stop_verbose_procedure()
{
    verbose_procedure = false;
}

int VirtualMachine::extract_number_from_program(unsigned int start_address, size_t *t)
{
    int r = -1;
    try
    {
        if (t == nullptr)
        {
            r = stoi(program.substr(start_address));
        } else
        {
            r = stoi(program.substr(start_address), t);
        }
    } catch (invalid_argument const &e)
    {
        error(INVALID_NUMBER);
    } catch (out_of_range const &e)
    {
        error(INVALID_NUMBER);
    }

    return r;
}

void VirtualMachine::message(const string &message)
{
    cout << message << endl;
}

string VirtualMachine::program_to_string()
{
    string s = "\n" + program;
    s += "\n";
    for (int i = 0; i < current_operator; i++) s += " ";
    s += PRINTING_POINTER;
    return s;
}

string VirtualMachine::memory_to_string()
{
    string s;
    int k = 0;
    for (int j = 0; j < ((size < MAX_SIZE_MEMORY_PRINT) ? size : MAX_SIZE_MEMORY_PRINT); j++)
    {
        s += (to_string(memory[j]) + " ");
        if (j == (int) (memory_ptr - memory)) k = (int) s.size() - 2;
    }
    s += "\n";
    for (int i = 0; i < k; i++) s += " ";
    s += PRINTING_POINTER;
    return s;

}

VirtualMachine::operator string()
{
    return program_to_string() + memory_to_string();
}

ostream &VirtualMachine::operator<<(ostream &o)
{
    o << (string) (*this);
    return o;
}

