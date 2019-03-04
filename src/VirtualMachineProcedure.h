//
// Created by emile on 26/02/19.
//

#ifndef LIFAP4_PROJECT_VIRTUAL_MACHINE_PROCEDURE_H
#define LIFAP4_PROJECT_VIRTUAL_MACHINE_PROCEDURE_H


#include "VirtualMachine.h"

#define PROC_PRINTING_MESSAGE (string)"[ PROC ]"

//Status macros
#define OUTPUTTING 101
#define INPUTTING 102

class VirtualMachineProcedure : public VirtualMachine
{
    //Status have special code in this class starting at 100.
protected:
    void val_out() override;

    void val_in() override;

    void error(int code) override;

    void message(const string &message) override;

public:
    VirtualMachineProcedure(const string &program, istream *in, ostream *out, int d, size_t size = 30000,
                            int *memory = nullptr);

    int output;

    void input(int inpt);

    explicit operator string() override;

    int depth;
};


#endif //LIFAP4_PROJECT_VIRTUAL_MACHINE_PROCEDURE_H
