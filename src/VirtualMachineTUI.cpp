//
// Created by emile on 12/03/19.
//

#include "VirtualMachineTUI.h"
#include "GameTUI.h"


VirtualMachineTUI::VirtualMachineTUI(const string &program_, istream *in_, ostream *out_, GameTUI *gt_, size_t size_,
                                     int *memory_) : VirtualMachine(program_, in_, out_, size_, memory_), gt(gt_)
{
}

void VirtualMachineTUI::update_tui()
{
    mvwprintw(gt->vm_output_win, 2, 2, "looper here");
    mvwprintw(gt->vm_program_win, LINES / 8, 2, program_to_string().c_str());
    mvwprintw(gt->vm_memory_win, LINES / 8, 8, program_to_string().c_str());
}

void VirtualMachineTUI::loop()
{
    if (verbose)
    {
        message(MESSAGE_LAUNCHING);
        cout << (string) (*this);
    }
    status = STATUS_RUNNING;
    while (status == STATUS_RUNNING)
    {
        update_tui();
        try
        {
            do_one_iteration();
        } catch (const VirtualMachineException &e)
        {
            error_handler(e);
            return;
        }

    }
}