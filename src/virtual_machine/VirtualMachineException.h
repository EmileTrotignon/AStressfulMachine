//
// Created by emile on 07/03/19.
//

#ifndef A_STRESSFUL_MACHINE_VIRTUALMACHINEEXCEPTION_H
#define A_STRESSFUL_MACHINE_VIRTUALMACHINEEXCEPTION_H

#include <iostream>

using namespace std;

class VirtualMachine;

/**
 * Exception base class. Derived a lot in this header, every class is a possible error of the VM
 */
class VirtualMachineException : public runtime_error
{
protected:

    string vm_state(const VirtualMachine *vm) const;

public:
    explicit VirtualMachineException(const VirtualMachine *vm, const string &msg = "Virtual Machine error");

    VirtualMachineException(const VirtualMachineException &e) noexcept = default;

    //const char *what() const noexcept override;
};

class VM_MemoryError : public VirtualMachineException
{

public:
    explicit VM_MemoryError(const VirtualMachine *vm, const char *msg);
};

class VM_OutOfMemory : public VM_MemoryError
{
public:
    explicit VM_OutOfMemory(const VirtualMachine *vm);
};

class VM_NegativeMemoryAccess : public VM_MemoryError
{

public:
    explicit VM_NegativeMemoryAccess(const VirtualMachine *vm);

};

class VM_SyntaxError : public VirtualMachineException
{

public:
    explicit VM_SyntaxError(const VirtualMachine *vm, const char *msg = "Syntax Error.");

};

class VM_UnmatchedPar : public VM_SyntaxError
{

public:
    explicit VM_UnmatchedPar(const VirtualMachine *vm, const char *msg = "Unmatched parenthesis char type");

};

class VM_UnmatchedCurlyBrackets : public VM_UnmatchedPar
{

public:
    explicit VM_UnmatchedCurlyBrackets(const VirtualMachine *vm);

};

class VM_UnmatchedBrackets : public VM_UnmatchedPar
{

public:
    explicit VM_UnmatchedBrackets(const VirtualMachine *vm);

};

class VM_InvalidNumber : public VM_SyntaxError
{
public:
    explicit VM_InvalidNumber(VirtualMachine *vm);
};

class VM_ProcError : public VirtualMachineException
{

public:
    explicit VM_ProcError(const VirtualMachine *vm, const char *msg = "Procedure related error_handler");

};


class VM_AskedOutputWhenInputting : public VM_ProcError
{

public:
    explicit VM_AskedOutputWhenInputting(const VirtualMachine *vm);

};

class VM_UnableToOpenFile : public VirtualMachineException
{

public:
    explicit VM_UnableToOpenFile(const VirtualMachine *vm, const string &file);

};

class VM_ErrorInProc : public VirtualMachineException
{
protected:
    const VirtualMachineException *error_in_proc;
public:
    explicit VM_ErrorInProc(VirtualMachine *vm, const VirtualMachineException *error_in_proc);
};

class UserInterrupt : public exception
{
public:
    UserInterrupt();
};

#endif //A_STRESSFUL_MACHINE_VIRTUALMACHINEEXCEPTION_H
