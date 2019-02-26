//
// Created by emile on 25/02/19.
//

#include "VirtualMachine.h"

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
    *out << *memory_ptr;
}

void VirtualMachine::char_out()
{
    *out << (char)*memory_ptr;
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

        case '!':
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

int *VirtualMachine::get_memory()
{
    return memory;
}

int *VirtualMachine::get_memory_ptr()
{
    return memory_ptr;
}
