//
// Created by emile on 07/03/19.
//

#include "VirtualMachineException.h"
#include "VirtualMachine.h"


VirtualMachineException::VirtualMachineException(const VirtualMachine *vm_) :
        exception(), vm(vm_)
{
    message = "Virtual Machine error_handler";
}

string VirtualMachineException::vm_state() const
{
    string r;
    if (vm->is_verbose()) r += "\n" + string((*vm));
    else r += " This Happened at char #" + to_string(*(vm->get_current_operator())) + "\n";
    return r;
}

const char *VirtualMachineException::what() const noexcept
{
    return (message + vm_state()).c_str();
}

VM_MemoryError::VM_MemoryError(const VirtualMachine *vm_) : VirtualMachineException(vm_)
{
    message = "Memory error_handler.";
}

VM_OutOfMemory::VM_OutOfMemory(const VirtualMachine *vm_) : VM_MemoryError(vm_)
{
    message = "VM out of memory.";
}

VM_NegativeMemoryAccess::VM_NegativeMemoryAccess(const VirtualMachine *vm_) : VM_MemoryError(vm_)
{
    message = "Negative memory access.";
}

VM_SyntaxError::VM_SyntaxError(const VirtualMachine *vm_) : VirtualMachineException(vm_)
{
    message = "Syntax Error.";
}

VM_UnmatchedPar::VM_UnmatchedPar(const VirtualMachine *vm_) : VM_SyntaxError(vm_)
{
    message = "Unmatched parenthesis typed char";
}

VM_UnmatchedBrackets::VM_UnmatchedBrackets(const VirtualMachine *vm_) : VM_UnmatchedPar(vm_)
{
    message = "Unmatched brackets.";
}

VM_UnmatchedCurlyBrackets::VM_UnmatchedCurlyBrackets(const VirtualMachine *vm_) : VM_UnmatchedPar(vm_)
{
    message = "Unmatched curly brackets.";
}

VM_InvalidNumber::VM_InvalidNumber(VirtualMachine *vm_) : VM_SyntaxError(vm_)
{
    message = "Invalid number.";
}

VM_ProcError::VM_ProcError(const VirtualMachine *vm_) : VirtualMachineException(vm_)
{
    message = "Procedure related error_handler";
}

VM_AskedOutputWhenInputting::VM_AskedOutputWhenInputting(const VirtualMachine *vm_) : VM_ProcError(vm_)
{
    message = "Tried to access procedure output when it needed input.";
}

VM_UnableToOpenFile::VM_UnableToOpenFile(const VirtualMachine *vm_, const string &file) : VirtualMachineException(vm_)
{
    message = "Unable to open file '" + file + "'.";

}

VM_ErrorInProc::VM_ErrorInProc(VirtualMachine *vm_, const VirtualMachineException *error_in_proc_)
        : VirtualMachineException(
        vm_), error_in_proc(error_in_proc_)
{
    message = "An error_handler occured in child procedure.";
}