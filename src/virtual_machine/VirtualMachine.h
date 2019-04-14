//
// Created by emile on 25/02/19.
//

#ifndef ASTRESSFULMACHINE_VIRTUALMACHINE_H
#define ASTRESSFULMACHINE_VIRTUALMACHINE_H

#include <iostream>
#include <vector>
#include <map>
#include <functional>

#include "../file_utilities/file_utilities.h"
#include "VirtualMachineException.h"
/*
const char* PRINTING_POINTER = "^\n";

// Status macros
const int STATUS_ERROR = -1;
const int STATUS_RUNNING = 1;
const int STATUS_PAUSED = 0;

// Message macros
const char* MESSAGE_LAUNCHING = "[ UNPAUSING VM ]";
const char* MESSAGE_FINISHED = "The execution is finished";
const char* MESSAGE_STARTING_PROCEDURE = "[ START PROCEDURE ]";
#define MESSAGE_DEPTH "[ DEPTH " + to_string(depth) + " ]"

// Syntax macros
const char SYNTAX_PTR_INCR =       '>';
const char SYNTAX_PTR_DINCR =      '<';
const char SYNTAX_VAL_INCR =       '+';
const char SYNTAX_VAL_DINCR =      '-';
const char SYNTAX_VAL_OUT =        '.';
const char SYNTAX_CHAR_OUT =       ':';
const char SYNTAX_VAL_IN =         ',';
const char SYNTAX_OPEN_GOTO =      '[';
const char SYNTAX_CLOSE_GOTO =     ']';
const char SYNTAX_GOTO_MARKER =    '|';
const char SYNTAX_COND_GREATER =   '>';
const char SYNTAX_COND_LESSER =    '<';
const char SYNTAX_COND_EQUAL =     '=';
const char SYNTAX_COND_DIFF =      '/';
const char SYNTAX_PTR_JUMP =       '^';
const char SYNTAX_PTR_RESET =      '#';
const char SYNTAX_VAL_RESET =      '_';
const char SYNTAX_DO_N_TIME =      '*';
const char SYNTAX_OPEN_PROC =      '{';
const char SYNTAX_CLOSE_PROC =     '}';
const char SYNTAX_TERMINATE_PROC=  '!';
const char SYNTAX_FILE_MARKER =    '~';
*/

#define PRINTING_POINTER "^\n"

// Status macros
//#define STATUS_ERROR -1
//#define STATUS_RUNNING 1
//#define STATUS_PAUSED 0

// Message macros
#define MESSAGE_LAUNCHING "[ UNPAUSING VM ]"
#define MESSAGE_FINISHED "The execution is finished"
#define MESSAGE_STARTING_PROCEDURE "[ START PROCEDURE ]"
#define MESSAGE_DEPTH "[ DEPTH " + to_string(depth) + " ]"

/*
// Syntax macros
#define SYNTAX_PTR_INCR        '>'
#define SYNTAX_PTR_DINCR       '<'
#define SYNTAX_VAL_INCR        '+'
#define SYNTAX_VAL_DINCR       '-'
#define SYNTAX_VAL_OUT         '.'
#define SYNTAX_CHAR_OUT        ':'
#define SYNTAX_VAL_IN          ','
#define SYNTAX_OPEN_GOTO       '['
#define SYNTAX_CLOSE_GOTO      ']'
#define SYNTAX_GOTO_MARKER     '|'
#define SYNTAX_COND_GREATER    '>'
#define SYNTAX_COND_LESSER     '<'
#define SYNTAX_COND_EQUAL      '='
#define SYNTAX_COND_DIFF       '/'
#define SYNTAX_PTR_JUMP        '^'
#define SYNTAX_PTR_RESET       '#'
#define SYNTAX_VAL_RESET       '_'
#define SYNTAX_DO_N_TIME       '*'
#define SYNTAX_OPEN_PROC       '{'
#define SYNTAX_CLOSE_PROC      '}'
#define SYNTAX_TERMINATE_PROC  '!'
#define SYNTAX_FILE_MARKER     '~'
*/
using namespace std;

class VirtualMachineProcedure;

class UnitTest;


/**
 * This is the language interpreter class
 */
class VirtualMachine
{
public:

    enum Status
    {
        s_error, s_running, s_paused, s_proc_inputting, s_proc_outputting
    };

    static const char SYNTAX_PTR_INCR = '>';  // Move the pointer to the right
    static const char SYNTAX_PTR_DINCR = '<'; // Move the pointer to the left
    static const char SYNTAX_VAL_INCR = '+'; // Increment the current cell's value
    static const char SYNTAX_VAL_DINCR = '-'; // Decrement the current cell's value
    static const char SYNTAX_VAL_OUT = '.'; // Output the current cell's value as a base 10 int
    static const char SYNTAX_CHAR_OUT = ':'; // Output the current cell's value a a char
    static const char SYNTAX_VAL_IN = ','; // Fetch an input and put it in the current cell
    static const char SYNTAX_OPEN_GOTO = '['; // Opening bracket for a goto anchor or a goto statement
    static const char SYNTAX_CLOSE_GOTO = ']'; // Close it
    static const char SYNTAX_GOTO_MARKER = '|'; // Signal the goto is not an anchor
    static const char SYNTAX_COND_GREATER = '>'; // Signal that the goto should only be done if the current cell's value is greater than 0
    static const char SYNTAX_COND_LESSER = '<'; // ___________ smaller than 0
    static const char SYNTAX_COND_EQUAL = '='; // ___________ equal to 0
    static const char SYNTAX_COND_DIFF = '/'; // ___________ different from 0
    static const char SYNTAX_PTR_JUMP = '^'; // Set the pointer d
    static const char SYNTAX_PTR_RESET = '#';
    static const char SYNTAX_VAL_RESET = '_';
    static const char SYNTAX_DO_N_TIME = '*';
    static const char SYNTAX_OPEN_PROC = '{';
    static const char SYNTAX_CLOSE_PROC = '}';
    static const char SYNTAX_TERMINATE_PROC = '!';
    static const char SYNTAX_FILE_MARKER = '~';

protected:

    istream *in; // The stream used to get the input
    ostream *out; // The stream used to output
    ostream *verbose_out; // The stream used to log information
    function<void(int)> output_callback; // Callback called each time the VM outputs
    string program; // The code
    string::iterator current_operator;
    vector<int> memory; // The internal memory of the VM
    vector<int>::iterator memory_ptr;
    Status status;
    bool print_errors; // In
    bool verbose;
    bool verbose_procedure;
    map<unsigned int, string::iterator> anchor_map;
    int depth;
    vector<string> include_directories;

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

    string file_to_string(const string &filename);

    void loop_procedure();

    void terminate_procedure();

    virtual void error_handler(const VirtualMachineException &error);

    int extract_number_from_program(size_t *t = nullptr);

    virtual void message(const string &message);

    /**
     * @brief This does one iteration of the execution
     */
    void do_one_iteration();

public:
    /**
     * @brief Constructor that initializes all the fields
     * @param program_ The code to be executed
     * @param in The input strestring("Solution initialisation throw exception : ") + string(e.what())am
     * @param out The output stream
     */
    /*
     * @param size The size of the memory. If the program starts with a number, this will be ignored
     * @param memory The memory to be used by the machine. Allocated automatically if not specified.
     */
    VirtualMachine(const string &program, istream *in, ostream *out, const vector<string> &include_directories = {},
                   const function<void(int)> output_callback = nullptr,
                   ostream *verbose_out = &cout);

    VirtualMachine(const VirtualMachine &vm) = default;

    ~VirtualMachine();

    /**
     * @brief This resets the class to its state after construction
     * @param in
     */
    void reset(istream *in);

    /**
     * @brief This execute the program until it halts.
     * @param func A function to be executed at each step of the loop. Basic use would be to slow down execution.
     */
    void loop(function<void(VirtualMachine *)> vm_callback = nullptr);

    /**
     * @brief Getter for member program
     * @return the program
     */
    const string &get_program() const;

    /**
     * @brief Setter for the program
     * @param program The new value
     */
    void set_program(const string &program);


    /**
     * @brief Getter for member current_operator
     * @return current_operator
     */
    string::iterator get_current_operator() const;

    /**
     * @brief Getter for member status
     * @return status
     */
    int get_status() const;

    /**
     * @brief Getter for member memory
     * @return memory
     */
    const vector<int> &get_memory() const;

    /**
     * @brief Getter for member memory_ptr
     * @return memory_ptr
     */
    vector<int>::iterator get_memory_ptr() const;

    /**
     * @brief Makes the VM verbose.
     */
    void be_verbose();

    /**
     * @brief Makes the VM silent.
     */
    void stop_verbose();

    bool is_verbose() const;

    /**
     * @brief Make the VM and its procedures verbose.
     */
    void be_verbose_procedure();

    /**
     * @brief Make the VM's procedures silent.
     */
    void stop_verbose_procedure();

    bool is_verbose_procedure() const;

    void start_printing_errors();

    void stop_printing_errors();

    bool is_printing_errors() const;

    void set_output_callback(const function<void(int)> &output_callback);

    virtual string memory_to_string() const;

    virtual string program_to_string() const;

    /**
     * @brief Convert the VM's current state into a string.
     * @return The VM's string representation
     */
    virtual explicit operator string() const;

    ostream &operator<<(ostream &o) const;

    friend UnitTest;
};


#endif //_VIRTUAL_MACHINE_H
