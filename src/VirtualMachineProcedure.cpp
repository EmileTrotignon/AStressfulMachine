//
// Created by emile on 26/02/19.
//

#include "VirtualMachineProcedure.h"

VirtualMachineProcedure::VirtualMachineProcedure(const string &program, istream *in, ostream *out, int d, size_t size,
                                                 int *memory) : VirtualMachine(program, in, out, size, memory)
{
    //Delegate constructor
    output = 0;
    depth = d;
}

void VirtualMachineProcedure::val_out()
{
    output = *memory_ptr;
    status = OUTPUTTING;
    if (verbose) cout << "[ PROC OUTPUTTING ] [ DEPTH " << depth << " ] " << endl;
}

void VirtualMachineProcedure::val_in()
{
    status = INPUTTING;
    if (verbose) cout << "[ PROC INPUTTING ] " DEPTH " " << endl;
}

void VirtualMachineProcedure::error(int code)
{
    cout << PROC_PRINTING_MESSAGE " " DEPTH " ";
    VirtualMachine::error(code);
}

void VirtualMachineProcedure::message(const string &message)
{
    cout << PROC_PRINTING_MESSAGE " " DEPTH " ";
    VirtualMachine::message(message);
}

void VirtualMachineProcedure::input(int inpt)
{
    *memory_ptr = inpt;
    loop();
}


VirtualMachineProcedure::operator string()
{
    return add_message_before_each_line(VirtualMachine::operator string(), PROC_PRINTING_MESSAGE " " DEPTH "  ");
}

