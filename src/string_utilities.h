//
// Created by emile on 25/02/19.
//

#ifndef BRAINFUCK_STRING_UTILITIES_H
#define BRAINFUCK_STRING_UTILITIES_H

#include <iostream>

using namespace std;

int corresponding_par(const string &s, char open, char close, unsigned int par_address);

int corresponding_par_backward(const string &s, char open, char close, unsigned int par_address);


#endif //BRAINFUCK_STRING_UTILITIES_H
