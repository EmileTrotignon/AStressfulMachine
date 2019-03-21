//
// Created by emile on 07/03/19.
//

#include <fstream>
#include "VirtualMachineException.h"
#include "VirtualMachine.h"

ofstream log("log");

VirtualMachineException::VirtualMachineException(const VirtualMachine *vm, const string &msg) :
        runtime_error((msg + vm_state(vm)).c_str())
{
}

string VirtualMachineException::vm_state(const VirtualMachine *vm) const
{
    string r;
    if (vm->is_verbose()) r += "\n" + string((*vm));
    else r += " This Happened at char #" + to_string(vm->get_current_operator() - vm->get_program().begin());
    return r;
}

VM_MemoryError::VM_MemoryError(const VirtualMachine *vm_, const char *msg) : VirtualMachineException(vm_, msg)
{
}

VM_OutOfMemory::VM_OutOfMemory(const VirtualMachine *vm_) : VM_MemoryError(vm_, "VM out of memory.")
{
}

VM_NegativeMemoryAccess::VM_NegativeMemoryAccess(const VirtualMachine *vm_) : VM_MemoryError(vm_,
                                                                                             "Negative memory access.")
{
}

VM_SyntaxError::VM_SyntaxError(const VirtualMachine *vm_, const char *msg) : VirtualMachineException(vm_, msg)
{
}

VM_UnmatchedPar::VM_UnmatchedPar(const VirtualMachine *vm_, const char *msg) : VM_SyntaxError(vm_, msg)
{
}

VM_UnmatchedBrackets::VM_UnmatchedBrackets(const VirtualMachine *vm_) : VM_UnmatchedPar(vm_, "Unmatched brackets.")
{
}

VM_UnmatchedCurlyBrackets::VM_UnmatchedCurlyBrackets(const VirtualMachine *vm_) : VM_UnmatchedPar(vm_,
                                                                                                  "Unmatched curly brackets.")
{
}

VM_InvalidNumber::VM_InvalidNumber(VirtualMachine *vm_) : VM_SyntaxError(vm_, "Invalid number.")
{
}

VM_ProcError::VM_ProcError(const VirtualMachine *vm_, const char *msg) : VirtualMachineException(vm_, msg)
{
}

VM_AskedOutputWhenInputting::VM_AskedOutputWhenInputting(const VirtualMachine *vm_) : VM_ProcError(vm_,
                                                                                                   "Tried to access procedure output when it needed input.")
{
}

VM_UnableToOpenFile::VM_UnableToOpenFile(const VirtualMachine *vm_, const string &file) : VirtualMachineException(vm_,
                                                                                                                  ("Unable to open file '" +
                                                                                                                   file +
                                                                                                                   "'.").c_str())
{
}

VM_ErrorInProc::VM_ErrorInProc(VirtualMachine *vm_, const VirtualMachineException *error_in_proc_)
        : VirtualMachineException(vm_, "An error occured in child procedure."),
          error_in_proc(error_in_proc_)
{
}