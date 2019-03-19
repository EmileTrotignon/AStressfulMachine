//
// Created by emile on 18/03/19.
//

#ifndef A_STRESSFUL_MACHINE_OCURSEDSTREAM_H
#define A_STRESSFUL_MACHINE_OCURSEDSTREAM_H

#include <iostream>
#include <sstream>

#include "Window.h"

// Explanations here : https://stackoverflow.com/questions/772355/how-to-inherit-from-stdostream
// Some more here : http://www.voidcn.com/article/p-vjnlygmc-gy.html

using namespace std;

namespace ncursespp
{

    class CursedBuffer : public streambuf
    {

    private:
        Window *window;
        int starty;
        int startx;
        int x_buffer;
        int current_y;
        int current_x;

        void print_to_win();

    public:
        CursedBuffer(Window *window_, int starty_, int startx_, int x_buffer_);

        int_type overflow(int_type c);

        streamsize xsputn(const char_type *s, streamsize count) override;

        int sync() override;
    };

    class OCursedStream : public basic_iostream<char>
    {
    private:
        CursedBuffer buf;

    public:
        OCursedStream(Window *win, int starty, int startx, int x_buffer = 0);

    };
}

#endif //A_STRESSFUL_MACHINE_OCURSEDSTREAM_H
