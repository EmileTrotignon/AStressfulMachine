//
// Created by emile on 25/02/19.
//

#ifndef BRAINFUCK_STRING_UTILITIES_H
#define BRAINFUCK_STRING_UTILITIES_H

#include <iostream>
#include <sstream>

using namespace std;

int corresponding_par(const string &s, char open, char close, unsigned int par_address);

int corresponding_par_backward(const string &s, char open, char close, unsigned int par_address);

string add_message_before_each_line(string s, string message);

string file_to_string(const string &filename);


#endif //BRAINFUCK_STRING_UTILITIES_H
