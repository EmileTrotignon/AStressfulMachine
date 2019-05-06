//
// Created by emile on 26/02/19.
//

#ifndef ASTRESSFULMACHINE_VIRTUALMACHINEPROCEDURE_H
#define ASTRESSFULMACHINE_VIRTUALMACHINEPROCEDURE_H


#include "VirtualMachine.h"

//#define PROC_PRINTING_MESSAGE (string)"[ PROC ]"

//Status macros
//#define STATUS_PROC_OUTPUTTING 101
//#define STATUS_PROC_INPUTTING 102

/**
 * This class is used by VirtualMachine to perform procedure calls.
 * Only the input and output and the verbose/error printing are changed.
 */
class VirtualMachineProcedure : public VirtualMachine
{

protected:

    static constexpr const char *PROC_PRINTING_MESSAGE = "[ PROC]";
    int output; /// Used to store the output
    VirtualMachine *master_vm; /// Parent VirtualMachine. May be in fact a VirtualMachineProcedure

    void val_out() override; /// Stop the execution and tell the parent vm the an output is available

    void val_in() override; /// Stop the execution to ask for an output.

    void error_handler(const VirtualMachineException &error) override;

    void message(const string &message) override;


public:
    /**
     * @brief This call the VirtualMachine constructor as a delegate constructor and initialize the new fields.
     */
    VirtualMachineProcedure(VirtualMachine *master_vm, const string &program_, int depth_,
                            const vector<fs::path> &include_directories = {}, ostream *verbose_out = &cout);

    /**
     * @brief This is used by VirtualMachine to access the output of the procedure.
     * @return The output of the procedure
     */
    int get_output();

    /**
     * @brief This is used by VirtualMachine to input to the procedure.
     * @param inpt The input in question
     */
    void input(int inpt);

    /**
     * Changes the string operator to include header that indicates the procedure depth
     * @return
     */
    explicit operator string() const override;

    int depth;
};


#endif //ASTRESSFULMACHINE_VIRTUALMACHINEPROCEDURE_H
