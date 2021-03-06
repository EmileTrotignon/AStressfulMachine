//
// Created by emile on 25/02/19.
//

#ifndef ASTRESSFULMACHINE_UTILITIES_H
#define ASTRESSFULMACHINE_UTILITIES_H

#include <iostream>
#include <sstream>
#include <vector>
#include <filesystem>

using namespace std;
namespace fs = filesystem;

string::iterator corresponding_par(const string &s, char open, char close, string::iterator par_address);

int corresponding_par_backward(const string &s, char open, char close, unsigned int par_address);

string file_to_string(const fs::path &filename);

void string_to_file(const string &content, const fs::path &filename);

vector<string> filesystem_ls(const fs::path &dir);

size_t size_of_longest_string(const vector<string> &vs);

#endif //ASTRESSFULMACHINE_UTILITIES_H
