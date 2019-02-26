//
// Created by emile on 25/02/19.
//

#include <fstream>
#include <assert.h>
#include "VirtualMachine.h"
#include "virtual_machine_procedure.h"

VirtualMachine::VirtualMachine(const string &p, istream *i, ostream *o, size_t s, int *m)
{
    program = p;
    in = i;
    out = o;
    size = s;
    memory = m;
    if (m == nullptr) memory = new int[s];
    memory_ptr = memory;
    current_operator = 0;
    status = PAUSED;
    procedure_call = nullptr;
}

VirtualMachine::~VirtualMachine()
{
    delete[] memory;
    delete procedure_call;
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
            loop_procedure();
            if (procedure_call->status == OUTPUTTING) *memory_ptr = procedure_call->output;
            else
            {
                if (procedure_call->status == INPUTTING)
                    cout << "Procedure error: tried to access procedure output when it still needed input. ";
                else if (procedure_call->status == PAUSED)
                    cout << "Procedure error: tried to access procedure output its execution was finished. ";
                cout << "This happenend at char #"
                     << current_operator << "and char #" << procedure_call->current_operator << " in procedure"
                     << endl;
                status = ERROR;
            }
        }
    }
}

void VirtualMachine::open_loop()
{
    if (!*memory_ptr)
    {
        int corresponding = corresponding_par(program, '[', ']', current_operator);
        if (corresponding != -1) current_operator = (unsigned int) corresponding;
        else
        {
            cout << "Syntax error : unmatched '[' at char #" << current_operator << endl;
            status = ERROR;
            return;
        }
    }
}

void VirtualMachine::close_loop()
{
    if (*memory_ptr)
    {
        int corresponding = corresponding_par_backward(program, '[', ']', current_operator);
        if (corresponding != -1) current_operator = (unsigned int) corresponding;
        else
        {
            cout << "Syntax error : unmatched ']' at char #" << current_operator << endl;
            status = ERROR;
            return;
        }
    }
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

void VirtualMachine::mem_dump()
{
    for (int j = 0; j < 255; j++)
    {
        if (memory + j == memory_ptr)
            cout << "[ " << memory[j] << " ] ";
        else cout << memory[j] << " ";
    }
    cout << endl;
}

void VirtualMachine::do_n_time()
{
    string number = program.substr(current_operator + 1);
    int n;
    size_t t;
    n = stoi(number, &t);
    //cout << endl << n << endl;
    current_operator = (unsigned int) t + 1;
    for (int j = 0; j < n; j++)
    {
        do_one_iteration(false);
        if (status != RUNNING) return;
    }
}

void VirtualMachine::call_procedure()
{
    //need work
    int i = corresponding_par(program, '{', '}', current_operator);
    if (i == -1)
    {
        cout << "Syntax error : unmatched '{' at char #" << current_operator << endl;
        status = ERROR;
        return;
    }
    string procedure = program.substr(current_operator + 1, (unsigned int) i);
    current_operator += i + 1;
    string code;
    if (procedure[0] == '~')
    {
        ifstream file(procedure.substr(1, string::npos));
        string c((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
        code = c;
    } else
    {
        code = procedure;
    }
    procedure_call = new VirtualMachineProcedure(code, nullptr, nullptr);
    loop_procedure();
}

void VirtualMachine::loop_procedure()
{
    assert(procedure_call != nullptr);
    procedure_call->loop();
    if (procedure_call->status == PAUSED)
    {
        delete procedure_call;
        procedure_call = nullptr;
    } else if (procedure_call->status == ERROR)
    {
        status = ERROR;
    }
}

void VirtualMachine::terminate_procedure()
{
    if (procedure_call == nullptr)
    {
        cout << "Procedure error: trying to terminate a procedure that does not exist at char #" << current_operator
             << endl;
        status = ERROR;
        return;
    }
    delete procedure_call;
    procedure_call = nullptr;
}

void VirtualMachine::do_one_iteration(bool advance)
{
    if (status != RUNNING) return;
    //cout << program[current_operator] << endl;
    switch (program[current_operator])
    {
        default:
            break;

        case '>':
            // This operator make the pointer point to the cell after the current cell
            ptr_incr();
            break;

        case '<':
            // This operator make the pointer point to the cell before the current cell
            ptr_dincr();
            break;

        case '+':
            // This operator increment the current value
            val_incr();
            break;

        case '-':
            // This operator decrement the current value
            val_dincr();
            break;

        case '.':
            // This operator output the current value as an int
            val_out();
            break;
        case ':':
            // This operator output the current value as a char
            char_out();
            break;

        case ',':
            // This operator input a value into the current cell
            val_in();
            break;

        case '[':
            // This operator jumps to the corresponding ']' if the current cell contains a 0
            open_loop();
            if (status != 1) return;
            break;

        case ']':
            // This operator jumps to the corresponding '[' if the current cell does not contains 0
            close_loop();
            if (status != 1) return;
            break;

        case '^':
            // This operator treats the current cell's content as a pointer and jumps to it.
            ptr_jump();
            break;

        case '#':
            // This operator make the pointed cell the cell 0
            ptr_reset();
            break;

        case '_':
            // This operator set the pointed cell's content to 0
            val_reset();
            break;

        case '*':
            // This operator's syntax is as follow : *NUMBER[OPERATOR]
            // for instance *100> will jump a 100 case to the right.
            // #*100> will set the current pointed case to be the 100th.
            do_n_time();
            break;

        case '@':
            mem_dump();
            break;

        case '{':
            call_procedure();
            break;

        case '!':
            terminate_procedure();
            break;
    }
    if (memory_ptr >= memory + size)
    {
        cout << "Runtime error : The VirtualMachine is out of memory. This happened at char #" << current_operator
             << endl;
        status = ERROR;
        return;
    }
    if (memory_ptr < memory)
    {
        cout << "Runtime error : The program tried to access negative memory. This happened at char #"
             << current_operator << endl;
        status = ERROR;
        return;
    }
    if (advance) current_operator++;
    if (current_operator >= program.size())
    {
        cout << "\nThe execution is finished" << endl;
        status = PAUSED;
    }
}

void VirtualMachine::loop()
{
    cout << "Lauching the Virtual Machine now" << endl;
    cout << program << endl;
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
