//
// Created by emile on 19/03/19.
//

#ifndef A_STRESSFUL_MACHINE_CURSEDSTRINGSTREAM_H
#define A_STRESSFUL_MACHINE_CURSEDSTRINGSTREAM_H

#include <iostream>

#include "ncurses++.h"

// http://www.math.hkbu.edu.hk/parallel/pgi/doc/pgC++_lib/stdlibug/cre_2288.htm

using namespace std;

namespace ncursespp
{
    class CursedStringBuffer : public stringbuf
    {
    private:
        Window *window;
        int starty;
        int startx;
        int x_buffer;
        int current_y;
        int current_x;

        void print_to_win(int_type ch = -1);

    public:

        CursedStringBuffer(Window *window_, int starty_, int startx_, int x_buffer_);

        int_type overflow(int_type ch) override;

        int sync() override;
    };

    class CursedStringStream : public basic_stringstream<char>
    {

    private:
        CursedStringBuffer buf;

    public:
        CursedStringStream(Window *window_, int starty_, int startx_, int x_buffer_);
    };

}
#endif //A_STRESSFUL_MACHINE_CURSEDSTRINGSTREAM_H
