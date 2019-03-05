//
// Created by emile on 26/02/19.
//

#ifndef ASTRESSFULMACHINE_VIRTUALMACHINEPROCEDURE_H
#define ASTRESSFULMACHINE_VIRTUALMACHINEPROCEDURE_H


#include "VirtualMachine.h"

#define PROC_PRINTING_MESSAGE (string)"[ PROC ]"

//Status macros
#define STATUS_PROC_OUTPUTTING 101
#define STATUS_PROC_INPUTTING 102

/**
 * This class is used by VirtualMachine to perform procedure calls.
 * It is only the input and output and the verbose/error printing that are changed.
 */
class VirtualMachineProcedure : public VirtualMachine
{
protected:
    void val_out() override;

    void val_in() override;

    void error(int code) override;

    void message(const string &message) override;

    int output;

public:
    /**
     * This call the VirtualMachine constructor as a delegate constructor and initialize the new fields.
     * @param program
     * @param in
     * @param out
     * @param depth The recursive depth of the procedure.
     * @param size
     * @param memory
     */
    VirtualMachineProcedure(const string &program, istream *in, ostream *out, int depth, size_t size = 30000,
                            int *memory = nullptr);

    /**
     * This should be used to access the output of the procedure.
     * @return The output of the procedure
     */
    int get_output();

    void input(int inpt);

    explicit operator string() override;

    int depth;
};


#endif //ASTRESSFULMACHINE_VIRTUALMACHINEPROCEDURE_H
