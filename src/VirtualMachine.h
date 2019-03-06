//
// Created by emile on 25/02/19.
//

#ifndef ASTRESSFULMACHINE_VIRTUALMACHINE_H
#define ASTRESSFULMACHINE_VIRTUALMACHINE_H

#include <iostream>
#include <vector>
#include <map>

#include "utilities.h"

#define MAX_SIZE_MEMORY_PRINT 10
#define PRINTING_POINTER "^\n"

// Status macros
#define STATUS_ERROR -1
#define STATUS_RUNNING 1
#define STATUS_PAUSED 0

// Error code macros
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

// Message macros
#define MESSAGE_LAUNCHING          "[ UNPAUSING VM ]"
#define MESSAGE_FINISHED           "The execution is finished"
#define MESSAGE_STARTING_PROCEDURE "[ START PROCEDURE ]"
#define MESSAGE_DEPTH              "[ DEPTH " + to_string(depth) + " ]"

// Syntax macro
#define SYNTAX_PTR_INCR       '>'
#define SYNTAX_PTR_DINCR      '<'
#define SYNTAX_VAL_INCR       '+'
#define SYNTAX_VAL_DINCR      '-'
#define SYNTAX_VAL_OUT        '.'
#define SYNTAX_CHAR_OUT       ':'
#define SYNTAX_VAL_IN         ','
#define SYNTAX_OPEN_GOTO      '['
#define SYNTAX_CLOSE_GOTO     ']'
#define SYNTAX_GOTO_MARKER    '|'
#define SYNTAX_COND_GREATER   '>'
#define SYNTAX_COND_LESSER    '<'
#define SYNTAX_COND_EQUAL     '='
#define SYNTAX_COND_DIFF      '/'
#define SYNTAX_PTR_JUMP       '^'
#define SYNTAX_PTR_RESET      '#'
#define SYNTAX_VAL_RESET      '_'
#define SYNTAX_DO_N_TIME      '*'
#define SYNTAX_OPEN_PROC      '{'
#define SYNTAX_CLOSE_PROC     '}'
#define SYNTAX_TERMINATE_PROC '!'
#define SYNTAX_FILE_MARKER    '~'

using namespace std;

class VirtualMachineProcedure;


/**
 * This is the language interpreter class
 */
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
    int depth;

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

    /**
     * Constructor that initializes all the fields
     * @param program The code to be executed
     * @param in The input stream
     * @param out The output stream
     * @param size The size of the memory. If the program starts with a number, this will be ignored
     * @param memory The memory to be used by the machine. Allocated automatically if not specified.
     */
    VirtualMachine(const string &program, istream *in, ostream *out, size_t size = 30000, int *memory = nullptr);

    ~VirtualMachine();

    /**
     * This do one iteration of the execution
     * @param advance This bool is here to tell the VM if it should advance in the program or redo the same operator next time.
     */
    void do_one_iteration(bool advance = true);

    /**
     * This execute the program until it halts.
     * @param func A function to be executed at each step of the loop. Basic use would be to slow down execution.
     */
    void loop(void (*func)() = nullptr);

    /**
     * Getter for member program
     * @return the program
     */
    string get_program();

    /**
     * Setter for the program
     * @param program The new value
     */
    void set_program(const string &program);

    /**
     * Getter for member size
     * @return size
     */
    size_t get_size();

    /**
     * Getter for member current_operator
     * @return current_operator
     */
    int get_current_operator();

    /**
     * Getter for member status
     * @return status
     */
    int get_status();

    /**
     * Getter for member memory
     * @return memory
     */
    int *get_memory();

    /**
     * Getter for member memory_ptr
     * @return memory_ptr
     */
    int *get_memory_ptr();

    /**
     * Makes the VM verbose.
     */
    void be_verbose();

    /**
     * Makes the VM silent.
     */
    void stop_verbose();

    /**
     * Make the VM and its procedures verbose.
     */
    void be_verbose_procedure();

    /**
     * Make the VM's procedures silent.
     */
    void stop_verbose_procedure();

    /**
     * Convert the VM's current state into a string.
     * @return The VM's string representation
     */
    virtual explicit operator string();

    ostream &operator<<(ostream &o);
};


#endif //_VIRTUAL_MACHINE_H
