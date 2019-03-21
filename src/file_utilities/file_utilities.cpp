//
// Created by emile on 25/02/19.
//

#include <fstream>
#include <filesystem>
#include "file_utilities.h"
#include <algorithm>


using namespace std;
namespace fs = std::filesystem;

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

    if (!fs::exists(dir)) throw runtime_error("The directory " + dir + " does not exists.");


    vector<string> saves;
    for (auto &entry : fs::directory_iterator(dir))
        saves.push_back(entry.path().filename());

    return saves;
}

