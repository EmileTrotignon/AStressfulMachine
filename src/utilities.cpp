//
// Created by emile on 25/02/19.
//

#include "utilities.h"

int corresponding_par(const string &s, char open, char close, unsigned int par_address)
{
    int depth = 1;
    int j = 0;
    while (depth != 0 && par_address + j < s.size())
    {
        j++;
        if (s[par_address + j] == open) depth++;
        if (s[par_address + j] == close) depth--;
    }
    if (depth == 0) return par_address + j;
    else return -1;
}

int corresponding_par_backward(const string &s, char open, char close, unsigned int par_address)
{
    int depth = 1;
    int j = 0;
    while (depth != 0 && par_address + j > 0)
    {
        j--;
        if (s[par_address + j] == open) depth--;
        if (s[par_address + j] == close) depth++;
    }
    if (depth == 0) return par_address + j;
    else return -1;
}

string add_message_before_each_line(string s, string message)
{
    istringstream stream(s);
    string r;
    string line;
    while (getline(stream, line))
    {
        r += message + line + "\n";
        line = "";
    }
    return r;
}
