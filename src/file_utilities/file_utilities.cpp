//
// Created by emile on 25/02/19.
//

#include <fstream>
#include <filesystem>
#include "file_utilities.h"
#include <algorithm>


using namespace std;
namespace fs = std::filesystem;

string file_to_string(const fs::path &filename)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        throw invalid_argument("Unable to open file '" + filename.string() + "'");
    }
    string c((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    file.close();
    return c;
}

void string_to_file(const string &content, const fs::path &filename)
{
    ofstream file(filename);
    file << content;
    file.close();
}

vector<string> filesystem_ls(const fs::path &dir) {

    if (!fs::exists(dir)) throw runtime_error("The directory " + dir.string() + " does not exists.");


    vector<string> saves;
    for (auto &entry : fs::directory_iterator(dir))
        saves.push_back(entry.path().filename().string());

    return saves;
}

