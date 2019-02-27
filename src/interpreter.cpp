#include <iostream>
#include "VirtualMachine.h"

using namespace std;

int main(int argc, char **argv)
{
    if (argc <= 1)
    {
        cout << "Please provide a program to be executed" << endl;
        return 0;
    }
    string program(argv[argc - 1]);
    VirtualMachine vm(program, &cin, &cout);
    //vm.be_verbose_procedure();
    vm.loop();
    return 0;
}