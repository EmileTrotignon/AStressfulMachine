#include <iostream>
#include <vector>
#include "VirtualMachine.h"

using namespace std;

int main(int argc, char **argv)
{
    if (argc <= 1)
    {
        cout << "Please provide a program to be executed" << endl;
        return 0;
    }
    string program(argv[1]);
    VirtualMachine vm(program, &cin, &cout);
    vm.loop();
    return 0;
}