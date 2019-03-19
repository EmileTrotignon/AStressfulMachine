//
// Created by emile on 25/02/19.
//

#include <fstream>
#include <assert.h>
#include "VirtualMachine.h"
#include "VirtualMachineProcedure.h"

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

bool is_operator(char ch)
{
    return (ch == SYNTAX_CHAR_OUT || ch == SYNTAX_CLOSE_GOTO || ch == SYNTAX_CLOSE_PROC || ch == SYNTAX_COND_DIFF ||
            ch == SYNTAX_COND_EQUAL || ch == SYNTAX_COND_GREATER || ch == SYNTAX_COND_LESSER ||
            ch == SYNTAX_DO_N_TIME ||
            ch == SYNTAX_FILE_MARKER || ch == SYNTAX_GOTO_MARKER || ch == SYNTAX_OPEN_GOTO || ch == SYNTAX_OPEN_PROC ||
            ch == SYNTAX_PTR_DINCR || ch == SYNTAX_PTR_INCR || ch == SYNTAX_PTR_JUMP || ch == SYNTAX_PTR_RESET ||
            ch == SYNTAX_TERMINATE_PROC || ch == SYNTAX_VAL_DINCR || ch == SYNTAX_VAL_IN || ch == SYNTAX_VAL_INCR ||
            ch == SYNTAX_VAL_OUT || ch == SYNTAX_VAL_RESET);
}

string::iterator corresponding_par(const string &s, char open, char close, string::iterator par_address)
{
    int depth = 1;
    int j = 0;
    while (depth != 0 && par_address + j < s.end())
    {
        j++;
        if (*(par_address + j) == open) depth++;
        if (*(par_address + j) == close) depth--;
    }
    if (depth == 0) return par_address + j;
    else throw invalid_argument("unmatched parenthesis");
}


VirtualMachine::VirtualMachine(const string &program_, istream *in_, ostream *out_) :
        program(program_), in(in_), out(out_)
{
    status = STATUS_PAUSED;

    // If program is a filename, open the file and use that as the program
    if (program[0] == SYNTAX_FILE_MARKER) program = file_to_string(program.substr(1));

    // If the program begins

    current_operator = program.begin();
    memory = vector<int>{0};
    if (isdigit(program[0]))
    {
        size_t t;
        size_t size;
        size = (size_t) extract_number_from_program(&t);
        memory.resize(size, 0);
        program = program.substr(t);
    }
    memory_ptr = memory.begin();
    procedure_call = nullptr;
    verbose = false;
    verbose_procedure = false;
    depth = 0;

    // Anchor map is used for the gotoes
    initialize_anchor_map();
}

VirtualMachine::VirtualMachine(const VirtualMachine &vm_)
{
    throw runtime_error("Copy constructor not implemented yet");
}

VirtualMachine::~VirtualMachine()
{
    delete procedure_call;
}

void VirtualMachine::reset(istream *in_)
{
    in = in_;
    current_operator = program.begin();
    memory_ptr = memory.begin();
    delete procedure_call;
    procedure_call = nullptr;
    verbose = false;
    verbose_procedure = false;
    depth = 0;
}

void VirtualMachine::initialize_anchor_map()
{
    while (current_operator < program.end())
    {
        if (*current_operator == SYNTAX_OPEN_GOTO && *(current_operator + 1) != SYNTAX_GOTO_MARKER)
        {
            current_operator++;
            size_t t;
            int anchor = extract_number_from_program(&t);
            anchor_map[anchor] = (int) t + current_operator;

        }
        current_operator++;
    }
    current_operator = program.begin();
}

void VirtualMachine::ptr_incr()
{
    if (memory_ptr == memory.end() - 1)
    {
        memory.push_back(0);
        memory_ptr = memory.end() - 2;
    }
    memory_ptr++;

}

void VirtualMachine::ptr_dincr()
{
    memory_ptr--;
}

void VirtualMachine::val_incr()
{
    (*memory_ptr)++;
}

void VirtualMachine::val_dincr()
{
    (*memory_ptr)--;
}

void VirtualMachine::val_out()
{
    if (procedure_call == nullptr)
    {
        *out << *memory_ptr;
        out->flush();
    } else
    {
        if (procedure_call->status == STATUS_PROC_INPUTTING)
        {
            procedure_call->input(*memory_ptr);
        } else
        {
            *out << *memory_ptr;
        }
    }
}


void VirtualMachine::char_out()
{
    *out << (char) *memory_ptr;
}

void VirtualMachine::val_in()
{
    if (procedure_call == nullptr)
    {
        *in >> *memory_ptr;
    } else
    {
        *memory_ptr = procedure_call->get_output();
    }
}

void VirtualMachine::handle_bracket()
{
    current_operator++;
    switch (*current_operator)
    {
        case SYNTAX_GOTO_MARKER:
            current_operator++;
            go_to_cond();
            break;
        default:
            exit_goto();
            return;
    }
}

void VirtualMachine::go_to_cond()
{
    if (*current_operator == SYNTAX_COND_EQUAL)
    {
        if (*memory_ptr == 0)
        {
            current_operator++;
            go_to();
            return;
        } else exit_goto();
    } else if (*current_operator == SYNTAX_COND_GREATER)
    {
        if (*memory_ptr > 0)
        {
            current_operator++;
            go_to();
            return;
        } else exit_goto();
    } else if (*current_operator == SYNTAX_COND_DIFF)
    {
        if (*memory_ptr != 0)
        {
            current_operator++;
            go_to();
            return;
        } else exit_goto();
    } else if (*current_operator == SYNTAX_COND_LESSER)
    {
        if (*memory_ptr < 0)
        {
            current_operator++;
            go_to();
            return;
        } else exit_goto();
    } else
    {
        go_to();
        return;
    }
}

void VirtualMachine::go_to()
{
    int anchor = extract_number_from_program(); //stoi(program.substr(current_operator, string::npos));
    go_to_anchor(anchor);
}

void VirtualMachine::go_to_anchor(int anchor)
{
    current_operator = anchor_map[anchor];
}

void VirtualMachine::exit_goto()
{
    try
    {
        string::iterator i = corresponding_par(program, SYNTAX_OPEN_GOTO, SYNTAX_CLOSE_GOTO, current_operator - 1);
        current_operator = i;

    } catch (const invalid_argument &e)
    {
        throw VM_UnmatchedBrackets(this);
    }

}

void VirtualMachine::ptr_jump()
{
    memory_ptr = memory.begin() + (*memory_ptr);
}

void VirtualMachine::ptr_reset()
{
    memory_ptr = memory.begin();
}

void VirtualMachine::val_reset()
{
    *memory_ptr = 0;
}

void VirtualMachine::do_n_time()
{
    current_operator++;
    string number = string(current_operator, program.end());
    int n;
    size_t t;
    n = extract_number_from_program(&t); //stoi(number, &t);
    current_operator = program.begin() + t;
    for (int j = 0; j < n; j++)
    {
        do_one_iteration(false);
        if (status != STATUS_RUNNING) return;
    }
}

void VirtualMachine::call_procedure()
{
    try
    {
        string::iterator i = corresponding_par(program, SYNTAX_OPEN_PROC, SYNTAX_CLOSE_PROC, current_operator);

        string procedure = string(current_operator + 1, i);
        string code;
        if (i - 1 == current_operator) // If there is no filename it mean a recursive call
        {
            code = program;
        } else
        {
            current_operator = i;
            if (procedure[0] == SYNTAX_FILE_MARKER)
            {
                code = file_to_string(procedure.substr(1, procedure.size() - 2));
                if (status == STATUS_ERROR) return;
            } else
            {
                code = procedure;
            }
        }
        if (verbose_procedure) message(MESSAGE_STARTING_PROCEDURE MESSAGE_DEPTH);
        procedure_call = new VirtualMachineProcedure(this, code, depth + 1);
        if (verbose_procedure) procedure_call->be_verbose();
        loop_procedure();
    } catch (const invalid_argument &e)
    {
        throw VM_UnmatchedCurlyBrackets(this);
    }


}

string VirtualMachine::file_to_string(string filename)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        throw VM_UnableToOpenFile(this, filename);
    }
    string c((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    return c;
}

void VirtualMachine::loop_procedure()
{
    procedure_call->loop();
    if (procedure_call->status == STATUS_PAUSED)
    {
        delete procedure_call;
        procedure_call = nullptr;
    }
}

void VirtualMachine::terminate_procedure()
{
    delete procedure_call;
    procedure_call = nullptr;
}

void VirtualMachine::error_handler(const VirtualMachineException &error)
{
    cout << error.what();
    status = STATUS_ERROR;
}

void VirtualMachine::do_one_iteration(bool advance)
{
    if (status != STATUS_RUNNING) return;

    //cout << program[current_operator] << endl;
    switch (*current_operator)
    {
        default:
            break;

        case SYNTAX_PTR_INCR:
            // This operator make the pointer point to the cell after the current cell
            ptr_incr();
            break;

        case SYNTAX_PTR_DINCR:
            // This operator make the pointer point to the cell before the current cell
            ptr_dincr();
            break;

        case SYNTAX_VAL_INCR:
            // This operator increment the current value
            val_incr();
            break;

        case SYNTAX_VAL_DINCR:
            // This operator decrement the current value
            val_dincr();
            break;

        case SYNTAX_VAL_OUT:
            // This operator output the current value as an int
            val_out();
            break;
        case SYNTAX_CHAR_OUT:
            // This operator output the current value as a char
            char_out();
            break;

        case SYNTAX_VAL_IN:
            // This operator input a value into the current cell
            val_in();
            break;

        case SYNTAX_OPEN_GOTO:
            // This operator jumps to the corresponding ']' if the current cell contains a 0
            handle_bracket();
            //if (status != 1) return;
            break;

        case SYNTAX_PTR_JUMP:
            // This operator treats the current cell's content as a pointer and jumps to it.
            ptr_jump();
            break;

        case SYNTAX_PTR_RESET:
            // This operator make the pointed cell the cell 0
            ptr_reset();
            break;

        case SYNTAX_VAL_RESET:
            // This operator set the pointed cell's content to 0
            val_reset();
            break;

        case SYNTAX_DO_N_TIME:
            // This operator's syntax is as follow : *NUMBER[OPERATOR]
            // for instance *100> will jump a 100 case to the right.
            // #*100> will set the current pointed case to be the 100th.
            do_n_time();
            break;

        case SYNTAX_OPEN_PROC:
            call_procedure();
            break;

        case SYNTAX_TERMINATE_PROC:
            terminate_procedure();
            break;
    }
    if (memory_ptr < memory.begin())
    {
        throw VM_NegativeMemoryAccess(this);
    }
    if (advance) current_operator++;
    if (verbose && status == STATUS_RUNNING) cout << (string) (*this);

}

void VirtualMachine::loop(function<void(VirtualMachine *)> vm_callback)
{
    if (verbose)
    {
        message(MESSAGE_LAUNCHING);
        cout << (string) (*this);
    }
    status = STATUS_RUNNING;
    while (status == STATUS_RUNNING)
    {
        while (current_operator < program.end() && !is_operator(*current_operator)) current_operator++;
        if (current_operator == program.end())
        {
            status = STATUS_PAUSED;
            if (verbose) message(MESSAGE_FINISHED);
            return;
        }
        if (vm_callback != nullptr) vm_callback(this);
        try
        {
            do_one_iteration();
            if (current_operator == program.end())
            {
                status = STATUS_PAUSED;
                if (verbose) message(MESSAGE_FINISHED);
                return;
            }
        } catch (const VirtualMachineException &e)
        {
            error_handler(e);
            return;
        }

    }
}

const string &VirtualMachine::get_program() const
{
    return program;
}

void VirtualMachine::set_program(const string &program_)
{
    program = program_;
}

string::iterator VirtualMachine::get_current_operator() const
{
    return current_operator;
}

int VirtualMachine::get_status() const
{
    return status;
}

const vector<int> &VirtualMachine::get_memory() const
{
    return memory;
}

vector<int>::iterator VirtualMachine::get_memory_ptr() const
{
    return memory_ptr;
}

void VirtualMachine::be_verbose()
{
    verbose = true;
}

void VirtualMachine::stop_verbose()
{
    verbose = false;
    verbose_procedure = false;
}

bool VirtualMachine::is_verbose() const
{
    return verbose;
}

void VirtualMachine::be_verbose_procedure()
{
    verbose = true;
    verbose_procedure = true;
}

void VirtualMachine::stop_verbose_procedure()
{
    verbose_procedure = false;
}

bool VirtualMachine::is_verbose_procedure() const
{
    return verbose_procedure;
}

void VirtualMachine::start_printing_errors()
{
    print_errors = true;
}

void VirtualMachine::stop_printing_errors()
{
    print_errors = false;
}

bool VirtualMachine::is_printing_errors() const
{
    return print_errors;
}

int VirtualMachine::extract_number_from_program(size_t *t)
{
    int r;
    try
    {
        if (t == nullptr)
        {
            r = stoi(string(current_operator, program.end() - 1));
        } else
        {
            r = stoi(string(current_operator, program.end() - 1), t);
        }
    } catch (invalid_argument const &e)
    {
        throw VM_InvalidNumber(this);
    } catch (out_of_range const &e)
    {
        throw VM_InvalidNumber(this);
    }

    return r;
}

void VirtualMachine::message(const string &message)
{
    cout << message << endl;
}

string VirtualMachine::program_to_string() const
{
    string s = "\n" + program;
    s += "\n";
    for (auto i = program.begin(); i < current_operator; i++) s += " ";
    s += PRINTING_POINTER;
    return s;
}

string VirtualMachine::memory_to_string() const
{
    string s;
    int k = 0;
    for (auto j = memory.begin(); j < memory.end(); j++)
    {
        s += (to_string(*j) + " ");
        if (j == memory_ptr) k = (int) s.size() - 2;
    }
    s += "\n";
    for (int i = 0; i < k; i++) s += " ";
    s += PRINTING_POINTER;
    return s;
}

VirtualMachine::operator string() const
{
    return program_to_string() + memory_to_string();
}

ostream &VirtualMachine::operator<<(ostream &o) const
{
    o << (string) (*this);
    return o;
}
