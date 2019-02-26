#include <iostream>
#include <vector>
#include "VirtualMachine.h"

using namespace std;

int main(int argc, char **argv)
{
    string program(argv[1]);
    VirtualMachine vm(program, &cin, &cout);
    vm.loop();
    return 0;
}