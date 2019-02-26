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

void VirtualMachineProcedure::input(int inpt)
{
    *memory_ptr = inpt;
    loop();
}
