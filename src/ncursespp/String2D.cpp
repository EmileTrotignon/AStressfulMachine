//
// Created by emile on 15/03/19.
//

#include <sstream>
#include "String2D.h"

String2D::String2D() : list<string>()
{
}

String2D::String2D(const string &s)
{
    istringstream sstr(s);
    while (!sstr.eof())
    {
        string buff;
        getline(sstr, buff);
        push_back(buff);
        buff = "";
    }
}

String2D::operator string() const
{
    string r;

    for (const auto &s: *this)
    {
        r += s;
        r += "\n";
    }

    return r;
}