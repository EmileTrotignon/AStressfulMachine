//
// Created by emile on 15/03/19.
//

#ifndef A_STRESSFUL_MACHINE_STRING2D_H
#define A_STRESSFUL_MACHINE_STRING2D_H

#include <iostream>
#include <list>

using namespace std;

class String2D : public list<string>
{
private:

public:

    String2D();

    explicit String2D(const string &s);

    explicit operator string() const;


};


#endif //A_STRESSFUL_MACHINE_STRING2D_H
