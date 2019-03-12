//
// Created by emile on 12/03/19.
//

#ifndef A_STRESSFUL_MACHINE_VIRTUALMACHINETUI_H
#define A_STRESSFUL_MACHINE_VIRTUALMACHINETUI_H


#include "VirtualMachine.h"

class GameTUI;

class VirtualMachineTUI : public VirtualMachine
{
private:
    GameTUI *gt;

    void update_tui();

public:

    VirtualMachineTUI(const string &program, istream *in, ostream *out, GameTUI *gt, size_t size = DEFAULT_MEMORY_SIZE,
                      int *memory = nullptr);

    void loop() override;
};


#endif //A_STRESSFUL_MACHINE_VIRTUALMACHINTUI_H
