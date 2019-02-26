//
// Created by emile on 25/02/19.
//

#ifndef BRAINFUCK_BRAINFUCK_ITERATION_H
#define BRAINFUCK_BRAINFUCK_ITERATION_H

#include <iostream>
#include "utilities.h"

// Status values
#define ERROR -1
#define RUNNING 1
#define PAUSED 0

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

public:

    VirtualMachine(const string &program, istream *in, ostream *out, size_t size = 30000, int *memory = nullptr);

    void do_one_iteration(bool advance = true);

    virtual void loop();

    size_t get_size();

    int get_current_operator();

    int get_status();

    int *get_memory();

    int *get_memory_ptr();

};


#endif //BRAINFUCK_BRAINFUCK_ITERATION_H
