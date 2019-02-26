//
// Created by emile on 25/02/19.
//

#ifndef BRAINFUCK_BRAINFUCK_ITERATION_H
#define BRAINFUCK_BRAINFUCK_ITERATION_H

#include <iostream>
#include "string_utilities.h"

using namespace std;

class VirtualMachine
{
private:
    void ptr_incr();

    void ptr_dincr();

    void val_incr();

    void val_dincr();

    void val_out();

    void val_in();

    void open_loop();

    void close_loop();

    // Syntax Extension
    void ptr_jump();

    void ptr_reset();

    void mem_dump();

    void do_n_time();

public:
    string program;
    istream *in;
    ostream *out;
    size_t size;
    char *memory;
    char *memory_ptr;
    unsigned int current_operator;
    int status;

    VirtualMachine(const string &program, istream *in, ostream *out, size_t size = 30000, char *memory = nullptr);

    void do_one_iteration(bool advance = true);

    void loop();
};


#endif //BRAINFUCK_BRAINFUCK_ITERATION_H
