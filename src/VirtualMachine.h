//
// Created by emile on 25/02/19.
//

#ifndef BRAINFUCK_BRAINFUCK_ITERATION_H
#define BRAINFUCK_BRAINFUCK_ITERATION_H

#include <iostream>
#include "utilities.h"

#define MEMORY_SIZE_PRINT 10

// Status macros
#define ERROR -1
#define RUNNING 1
#define PAUSED 0

// Error code macros
#define OUT_OF_MEMORY                 1
#define NEGATIVE_MEMORY_ACCESS        2
#define UNMATCHED_OPEN_BRACKET        3
#define UNMATCHED_CLOSED_BRACKET      4
#define UNMATCHED_CURLY_BRACKET       5
#define PROC_ASK_OUTPUT_WITHOUT_INPUT 6
#define PROC_ASK_OUPUT_WHEN_FINISHED  7
#define UNABLE_TO_OPEN_FILE           8
#define TERMINATE_NONEXISTING_PROC    9
#define ERROR_IN_PROC                 10

using namespace std;

class VirtualMachineProcedure;

class VirtualMachine
{
protected:

    string program;
    istream *in;
    ostream *out;
    size_t size;
    int *memory;
    int *memory_ptr;
    unsigned int current_operator;
    int status; // 1 means running, 0 means stopped, and -1 mean an error occurred.
    bool verbose;
    bool verbose_procedure;

    VirtualMachineProcedure *procedure_call;

    void ptr_incr();

    void ptr_dincr();

    void val_incr();

    void val_dincr();

    virtual void val_out();

    void char_out();

    virtual void val_in();

    void open_loop();

    void close_loop();

    // Syntax Extension
    void ptr_jump();

    void ptr_reset();

    void val_reset();

    void mem_dump();

    void do_n_time();

    void call_procedure();

    void loop_procedure();

    void terminate_procedure();

    virtual void error(int code);

public:

    VirtualMachine(const string &program, istream *in, ostream *out, size_t size = 30000, int *memory = nullptr);

    ~VirtualMachine();

    void do_one_iteration(bool advance = true);

    virtual void loop();

    size_t get_size();

    int get_current_operator();

    int get_status();

    int *get_memory();

    int *get_memory_ptr();

    void be_verbose();

    void stop_verbose();

    void be_verbose_procedure();

    void stop_verbose_procedure();

    virtual string memory_to_string();

    virtual string program_to_string();

    virtual explicit operator string();

    ostream &operator<<(ostream &o);
};


#endif //BRAINFUCK_BRAINFUCK_ITERATION_H
