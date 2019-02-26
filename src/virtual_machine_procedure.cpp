//
// Created by emile on 26/02/19.
//

#include "virtual_machine_procedure.h"

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

void VirtualMachineProcedure::loop()
{
    cout << "Lauching the Virtual Machine now" << endl;
    cout << program << endl;
    status = RUNNING;
    while (status == RUNNING)
    {
        do_one_iteration();
    }
}