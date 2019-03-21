//
// Created by emile on 07/03/19.
//

#ifndef A_STRESSFUL_MACHINE_VIRTUALMACHINEEXCEPTION_H
#define A_STRESSFUL_MACHINE_VIRTUALMACHINEEXCEPTION_H

#include <iostream>

/*
#define ERROR_RUNTIME                       0
#define ERROR_OUT_OF_MEMORY                 1
#define ERROR_NEGATIVE_MEMORY_ACCESS        2
#define ERROR_UNMATCHED_OPEN_BRACKET        3
#define ERROR_UNMATCHED_CLOSED_BRACKET      4
#define ERROR_UNMATCHED_CURLY_BRACKET       5
#define ERROR_PROC_ASK_OUTPUT_WITHOUT_INPUT 6
#define ERROR_PROC_ASK_OUPUT_WHEN_FINISHED  7
#define ERROR_UNABLE_TO_OPEN_FILE           8
#define ERROR_TERMINATE_NONEXISTING_PROC    9
#define ERROR_IN_PROC                       10
#define ERROR_INVALID_NUMBER                11
#define ERROR_LOOP_NONEXISTING_PROC         12
*/
using namespace std;

class VirtualMachine;

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

#endif //A_STRESSFUL_MACHINE_VIRTUALMACHINEEXCEPTION_H
