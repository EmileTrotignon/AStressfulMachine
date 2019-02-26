//
// Created by emile on 25/02/19.
//

#include "VirtualMachine.h"

VirtualMachine::VirtualMachine(const string &p, istream *i, ostream *o, size_t s, char *m)
{
    program = p;
    in = i;
    out = o;
    size = s;
    memory = m;
    if (m == nullptr) memory = new char[s];
    memory_ptr = memory;
    current_operator = 0;
    status = 0;
    procedure_call = nullptr;
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
    *out << (int) *memory_ptr << " ";
    out->flush();
}

void VirtualMachine::val_in()
{
    *in >> *memory_ptr;
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
            status = -1;
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
            status = -1;
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
            cout << "[ " << (int) memory[j] << " ] ";
        else cout << (int) memory[j] << " ";
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
        if (status != 1) return;
    }
}


void VirtualMachine::do_one_iteration(bool advance)
{
    if (status != 1) return;
    //cout << program[current_operator] << endl;
    switch (program[current_operator])
    {
        default:
            break;

        case '>':
            ptr_incr();
            break;

        case '<':
            ptr_dincr();
            break;

        case '+':
            val_incr();
            break;

        case '-':
            val_dincr();
            break;

        case '.':
            val_out();
            break;

        case ',':
            val_in();
            break;

        case '[':
            open_loop();
            if (status != 1) return;
            break;

        case ']':
            close_loop();
            if (status != 1) return;
            break;

            // Syntax Extension
        case '^':
            // This operator treats the current case as a pointer and jumps to it.
            ptr_jump();
            break;

        case '#':
            // This operator make the pointed case the case 0
            ptr_reset();
            break;

        case '!':
            // This operator set the pointed case value to 0
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

        case '$':
            break;
    }
    if (memory_ptr >= memory + size)
    {
        cout << "Runtime error : The VirtualMachine is out of memory. This happened at char #" << current_operator
             << endl;
        status = -1;
        return;
    }
    if (memory_ptr < memory)
    {
        cout << "Runtime error : The program tried to access negative memory. This happened at char #"
             << current_operator << endl;
        status = -1;
        return;
    }
    if (advance) current_operator++;
    if (current_operator >= program.size())
    {
        cout << "\nThe execution is finished" << endl;
        status = 0;
    }
}

void VirtualMachine::loop()
{
    cout << "Lauching the Virtual Machine now" << endl;
    cout << program << endl;
    status = 1;
    while (status == 1)
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

char *VirtualMachine::get_memory()
{
    return memory;
}

char *VirtualMachine::get_memory_ptr()
{
    return memory_ptr;
}
