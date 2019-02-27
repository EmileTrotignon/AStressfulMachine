//
// Created by emile on 26/02/19.
//

#include "VirtualMachineProcedure.h"

VirtualMachineProcedure::VirtualMachineProcedure(const string &program, istream *in, ostream *out, size_t size,
                                                 int *memory) : VirtualMachine(program, in, out, size, memory)
{
    //Delegate constructor
    output = 0;
}

void VirtualMachineProcedure::val_out()
{
    output = *memory_ptr;
    status = OUTPUTTING;
}

void VirtualMachineProcedure::val_in()
{
    status = INPUTTING;
}

void VirtualMachineProcedure::error(int code)
{
    cout << PROC_PRINTING_MESSAGE;
    VirtualMachine::error(code);
}

void VirtualMachineProcedure::input(int inpt)
{
    *memory_ptr = inpt;
    loop();
}

VirtualMachineProcedure::operator string()
{
    string s = PROC_PRINTING_MESSAGE + program;
    s += "\n" + PROC_PRINTING_MESSAGE;
    for (int i = 0; i < current_operator; i++) s += " ";
    s += "^\n" + PROC_PRINTING_MESSAGE;
    for (int j = 0; j < 100; j++)
    {
        s += (to_string(memory[j]) + " ");
    }
    s += "\n" + PROC_PRINTING_MESSAGE;
    for (int i = 0; i < (int) (memory_ptr - memory) * 2; i++) s += " ";
    s += "^\n";
    return s;
}

