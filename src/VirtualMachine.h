//
// Created by emile on 25/02/19.
//

#ifndef BRAINFUCK_BRAINFUCK_ITERATION_H
#define BRAINFUCK_BRAINFUCK_ITERATION_H

#include <iostream>
#include <vector>
#include <map>
#include "utilities.h"

#define MAX_SIZE_MEMORY_PRINT 10

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
#define INVALID_NUMBER                11
#define LOOP_NONEXISTING_PROC         12

// Message macros
#define LAUNCHING          "Lauching the Virtual Machine now"
#define FINISHED           "The execution is finished"
#define STARTING_PROCEDURE "[ START PROCEDURE ]"

// Syntax macro
#define PTR_INCR       '>'
#define PTR_DINCR      '<'
#define VAL_INCR       '+'
#define VAL_DINCR      '-'
#define VAL_OUT        '.'
#define CHAR_OUT       ':'
#define VAL_IN         ','
#define OPEN_GOTO      '['
#define CLOSE_GOTO     ']'
#define GOTO_MARKER    '|'
#define COND_GREATER   '>'
#define COND_LESSER    '<'
#define COND_EQUAL     '='
#define COND_DIFF      '/'
#define PTR_JUMP       '^'
#define PTR_RESET      '#'
#define VAL_RESET      '_'
#define DO_N_TIME      '*'
#define OPEN_PROC      '{'
#define CLOSE_PROC     '}'
#define TERMINATE_PROC '!'
#define FILE_MARKER    '~'
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
    map<unsigned int, unsigned int> anchor_map;

    VirtualMachineProcedure *procedure_call;

    void initialize_anchor_map();

    void ptr_incr();

    void ptr_dincr();

    void val_incr();

    void val_dincr();

    virtual void val_out();

    void char_out();

    virtual void val_in();

    void handle_bracket();

    void go_to_cond();

    void go_to();

    void go_to_anchor(int anchor);

    void exit_goto();

    void ptr_jump();

    void ptr_reset();

    void val_reset();

    void do_n_time();

    void call_procedure();

    string file_to_string(string filename);

    void loop_procedure();

    void terminate_procedure();

    virtual void error(int code);

    int extract_number_from_program(unsigned int start_address, size_t *t=nullptr);

    virtual void message(const string &message);

    virtual string memory_to_string();

    virtual string program_to_string();

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

    virtual explicit operator string();

    ostream &operator<<(ostream &o);
};


#endif //BRAINFUCK_BRAINFUCK_ITERATION_H
