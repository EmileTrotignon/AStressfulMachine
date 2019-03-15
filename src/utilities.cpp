//
// Created by emile on 25/02/19.
//

#include <stdio.h>
#include <fstream>
#include <filesystem>
#include "utilities.h"
#include <ncurses.h>
#include <algorithm>


using namespace std;
namespace fs = std::filesystem;

string::iterator corresponding_par(const string &s, char open, char close, string::iterator par_address)
{
    int depth = 1;
    int j = 0;
    while (depth != 0 && par_address + j < s.end())
    {
        j++;
        if (*(par_address + j) == open) depth++;
        if (*(par_address + j) == close) depth--;
    }
    if (depth == 0) return par_address + j;
    else throw invalid_argument("unmatched parenthesis");
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

string file_to_string(const string &filename)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        throw invalid_argument("Unable to open file '" + filename + "'");
    }
    string c((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    return c;
}

vector<string> filesystem_ls(const string &dir)
{

    if (!fs::exists(dir)) throw runtime_error("dossier inexistant");


    vector<string> saves;
    for (auto &entry : fs::directory_iterator(dir))
        saves.push_back(entry.path().filename());

    return saves;
}

bool comp_str(const string &s1, const string &s2)
{
    return s1.size() < s2.size();
}

size_t size_of_longest_string(const vector<string> &vs)
{
    return max_element(vs.begin(), vs.end(), comp_str)->size();
}