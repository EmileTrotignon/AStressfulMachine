//
// Created by emile on 26/02/19.
//

#include "VirtualMachineProcedure.h"

string add_message_before_each_line(string s, string message)
{
    istringstream stream(s);
    string r;
    string line;
    while (getline(stream, line))
    {
        r += message + line + "\n";
        line = "";
    }
    return r;
}

VirtualMachineProcedure::VirtualMachineProcedure(VirtualMachine *master_vm_, const string &program_, int depth_) :
        VirtualMachine(program_, nullptr, nullptr), master_vm(master_vm_), depth(depth_)
{
    //Delegate constructor
    output = 0;
}

void VirtualMachineProcedure::val_out()
{
    output = *memory_ptr;
    status = STATUS_PROC_OUTPUTTING;
    if (verbose) cout << "[ PROC STATUS_PROC_OUTPUTTING ] [ MESSAGE_DEPTH " << depth << " ] " << endl;
}

void VirtualMachineProcedure::val_in()
{
    status = STATUS_PROC_INPUTTING;
    if (verbose) cout << "[ PROC STATUS_PROC_INPUTTING ] " MESSAGE_DEPTH " " << endl;
}

void VirtualMachineProcedure::error_handler(const VirtualMachineException &error)
{
    VirtualMachine::error_handler(error);
    throw VM_ErrorInProc(master_vm, &error); // Not good
}

void VirtualMachineProcedure::message(const string &message)
{
    cout << PROC_PRINTING_MESSAGE " " MESSAGE_DEPTH " ";
    VirtualMachine::message(message);
}

void VirtualMachineProcedure::input(int inpt)
{
    *memory_ptr = inpt;
    loop();
}

int VirtualMachineProcedure::get_output()
{
    if (status != STATUS_PROC_OUTPUTTING)
    {
        error_handler(VM_AskedOutputWhenInputting(this));
    }
    return output;
}

VirtualMachineProcedure::operator string() const
{
    return add_message_before_each_line(VirtualMachine::operator string(),
                                        PROC_PRINTING_MESSAGE " " MESSAGE_DEPTH "  ");
}
