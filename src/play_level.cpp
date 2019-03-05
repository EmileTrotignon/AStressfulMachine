//
// Created by emile on 04/03/19.
//

#include <iostream>
#include "GameLevel.h"

using namespace std;

int main(int argc, char **argv)
{
    if (argc <= 1)
    {
        cout << "Please provide a level to complete" << endl;
        return 0;
    }
    string level(argv[1]);
    GameLevel gl(level);
    gl.play();
    return 0;
}