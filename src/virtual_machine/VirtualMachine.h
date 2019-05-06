//
// Created by emile on 25/02/19.
//

#ifndef ASTRESSFULMACHINE_VIRTUALMACHINE_H
#define ASTRESSFULMACHINE_VIRTUALMACHINE_H

#include <iostream>
#include <vector>
#include <map>
#include <functional>
#include <filesystem>

#include "../file_utilities/file_utilities.h"
#include "VirtualMachineException.h"


#define PRINTING_POINTER "^\n"

// Message macros
/*#define MESSAGE_LAUNCHING "[ UNPAUSING VM ]"
#define MESSAGE_FINISHED "The execution is finished"
#define MESSAGE_STARTING_PROCEDURE "[ START PROCEDURE ]"*/

using namespace std;
namespace fs = filesystem;

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

    static constexpr char SYNTAX_PTR_INCR = '>';  /// Operator : Move the pointer to the right
    static constexpr char SYNTAX_PTR_DINCR = '<'; /// Operator : Move the pointer to the left
    static constexpr char SYNTAX_VAL_INCR = '+'; /// Operator : Increment the current cell's value
    static constexpr char SYNTAX_VAL_DINCR = '-'; /// Operator : Decrement the current cell's value
    static constexpr char SYNTAX_VAL_OUT = '.'; /// Operator : Output the current cell's value as a base 10 int
    static constexpr char SYNTAX_CHAR_OUT = ':'; /// Operator : Output the current cell's value a a char
    static constexpr char SYNTAX_VAL_IN = ','; /// Operator : Fetch an input and put it in the current cell
    static constexpr char SYNTAX_OPEN_GOTO = '['; /// Operator : Opening bracket for a goto anchor or a goto statement
    static constexpr char SYNTAX_CLOSE_GOTO = ']'; /// Operator : Close it
    static constexpr char SYNTAX_GOTO_MARKER = '|'; /// Operator : Signal the goto is not an anchor
    static constexpr char SYNTAX_COND_GREATER = '>'; /// Operator : Signal that the goto should only be done if the current cell's value is greater than 0
    static constexpr char SYNTAX_COND_LESSER = '<'; /// Operator : ___________ smaller than 0
    static constexpr char SYNTAX_COND_EQUAL = '='; /// Operator : ___________ equal to 0
    static constexpr char SYNTAX_COND_DIFF = '/'; /// Operator : ___________ different from 0
    static constexpr char SYNTAX_PTR_JUMP = '^'; /// Operator : Set the pointer d
    static constexpr char SYNTAX_PTR_RESET = '#'; /// Operator : Set the pointer to 0
    static constexpr char SYNTAX_VAL_RESET = '_'; /// Operator : Set the current cell's value to 0
    static constexpr char SYNTAX_DO_N_TIME = '*'; /// Operator : *14+ evaluate the '+' 14 times
    static constexpr char SYNTAX_OPEN_PROC = '{'; /// Operator : Opening delimiter for procedures
    static constexpr char SYNTAX_CLOSE_PROC = '}'; /// Operator : Closing delimiter for procedures
    static constexpr char SYNTAX_TERMINATE_PROC = '!'; /// Operator : Terminate the current procedure before it ends
    static constexpr char SYNTAX_FILE_MARKER = '~'; /// Used at the beginning of a program or procedure. Indicate that the program/procedure is stored in a file. Put the filename just after it.

protected:

    static constexpr const char *MESSAGE_LAUNCHING = "[ UNPAUSING VM ]";
    static constexpr const char *MESSAGE_FINISHED = "The execution is finished";
    static constexpr const char *MESSAGE_STARTING_PROCEDURE = "[ START PROCEDURE ]";



    istream *in; /// The stream used to get the input
    ostream *out; /// The stream used to output
    ostream *verbose_out; /// The stream used to log information
    function<void(int)> output_callback; /// Callback called each time the VM outputs
    string program; /// The code
    string::iterator current_operator;
    vector<int> memory; /// The internal memory of the VM
    vector<int>::iterator memory_ptr; /// The iterator to the current cell
    Status status; /// Indicate whether the VM is paused or running or raised an error
    bool print_errors; /// Indicate whether the VM should output errors in standard ouput
    bool verbose; /// Indicate whether the VM are verbose
    bool verbose_procedure; /// Indicate whether the VM's procedure are verbose
    map<unsigned int, string::iterator> anchor_map; /// Maps anchors location for gotoes
    int depth; /// Indicate the recursive depth (always 0 for this class, become positive in procedures only)
    int n_steps; /// Count the number of steps executed by the VM
    vector<fs::path> include_directories; /// Directories from which

    VirtualMachineProcedure *procedure_call; /// Pointer to the procedure

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

    string get_message_for_depth() const;

    /**
     * @brief Handle an error
     * Print it if member verbose_error is true
     * Change member status
     * Rethrow the error
     * Virtual in order to be able to change the printing in a derived class.
     * @param error the error to be handled
     */
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
     * @param include_directories The directories where procedures are stored
     * @param output_callback The callback that is called each time a value is outputted
     * @param verbose_out The stream for verbose outputting
     */
    /*
     * @param size The size of the memory. If the program starts with a number, this will be ignored
     * @param memory The memory to be used by the machine. Allocated automatically if not specified.
     */
    VirtualMachine(string program, istream *in, ostream *out, vector<fs::path> include_directories = {},
                   function<void(int)> output_callback = nullptr,
                   ostream *verbose_out = &cout);

    VirtualMachine(const VirtualMachine &vm) = default;

    ~VirtualMachine();

    /**
     * @brief This execute the program until it halts.
     * @param func A function to be executed at each step of the loop. Basic use would be to slow down execution.
     */
    void loop(const function<void(VirtualMachine *)> &vm_callback = nullptr);

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

    int get_n_steps();

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
     * Being verbose means that the state of the VM will be printed to standard output at each operation
     */
    void be_verbose();

    /**
     * @brief Makes the VM silent.
     * That is the default state of the VM
     */
    void stop_verbose();

    /**
     * @brief Indicates whether the VM is verbose or not.
     * @return True if the VM is verbose else false.
     */
    bool is_verbose() const;

    /**
     * @brief Make the VM and its procedures verbose.
     * @warning Not recursive, the procedures' procedures will not be verbose
     */
    void be_verbose_procedure();

    /**
     * @brief Make the VM's procedures silent.
     */
    void stop_verbose_procedure();

    /**
     * @brief Indicates whether the VM and its procedures are verbose or not.
     * @return True if the VM and its procedures are verbose, else false.
     */
    bool is_verbose_procedure() const;

    /**
     * @brief Make the VM print errors
     */
    void start_printing_errors();

    /**
     * Make the VM stop printing errors
     */
    void stop_printing_errors();


    /**
     *
     * @return True if the VM is printing errors else false.
     */
    bool is_printing_errors() const;

    /**
     * @brief Set a callback to be called each time a output is outputted
     * @param output_callback This function has the int that is being outputted as a parameter.
     */
    void set_output_callback(const function<void(int)> &output_callback);

    /**
     * @brief Convert the current state of memory into a printable (two line) string.
     * The string is two line long, with the memory in the first line,
     * and a '^' char placed under the current memory cell in the second.
     * @return The current state of the memory as a string.
     */

    virtual string memory_to_string() const;


    /**
     * @brief Convert the program that is being executed into a printable (two line) string.
     * The string is two line long, with the program in the first line,
     * and a '^' char placed under the current operator in the second.
     * @warning Fails if there are any line return in the program : this only to be used for simple one line program,
     * if you want to debug longer programs use the Qt GUI
     * @return The program as a two line string
     */

    virtual string program_to_string() const;

    /**
     * @brief Convert the VM's current state into a string.
     *
     * @warning Only use with one line programs. See VirtualMachine::program_to_string's doc for explanation.
     * @return The VM's string representation
     */
    virtual explicit operator string() const;

    /**
     * @brief Output the VM's current state to o.
     * @warning Only use with one line programs. See VirtualMachine::program_to_string's doc for explanation.
     */
    ostream &operator<<(ostream &o) const;

    friend UnitTest;
};


#endif //_VIRTUAL_MACHINE_H
