//
// Created by emile on 26/02/19.
//

#include "VirtualMachineProcedure.h"

string add_message_before_each_line(const string &s, const string &message)
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

VirtualMachineProcedure::VirtualMachineProcedure(VirtualMachine *master_vm_, const string &program_, int depth_,
                                                 const vector<fs::path> &include_directories, ostream *verbose_out_) :
        VirtualMachine(program_, nullptr, nullptr, include_directories, nullptr, verbose_out_), master_vm(master_vm_),
        depth(depth_)
{
    //Delegate constructor
    output = 0;
}

void VirtualMachineProcedure::val_out()
{
    output = *memory_ptr;
    status = s_proc_outputting;
    if (verbose) *verbose_out << "[ PROC STATUS_PROC_OUTPUTTING ] [ MESSAGE_DEPTH " << depth << " ] " << endl;
}

void VirtualMachineProcedure::val_in()
{
    status = s_proc_inputting;
    if (verbose) *verbose_out << "[ PROC STATUS_PROC_INPUTTING ] " + get_message_for_depth() + " " << endl;
}

void VirtualMachineProcedure::error_handler(const VirtualMachineException &error)
{
    VirtualMachine::error_handler(error);
    //throw VM_ErrorInProc(master_vm, &error); // Not good
}

void VirtualMachineProcedure::message(const string &message)
{
    *verbose_out << string(PROC_PRINTING_MESSAGE) + " " + get_message_for_depth() + " ";
    VirtualMachine::message(message);
}

void VirtualMachineProcedure::input(int inpt)
{
    *memory_ptr = inpt;
    loop();
}

int VirtualMachineProcedure::get_output()
{
    if (status != s_proc_outputting)
    {
        error_handler(VM_AskedOutputWhenInputting(this));
    }
    return output;
}

VirtualMachineProcedure::operator string() const
{
    return add_message_before_each_line(VirtualMachine::operator string(),
                                        string(PROC_PRINTING_MESSAGE) + " " + get_message_for_depth() + "  ");
}

