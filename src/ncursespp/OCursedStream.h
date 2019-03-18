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

    public:
        CursedBuffer(Window *window_, int starty_, int startx_, int x_buffer_);

        int overflow(int ch) override;

        int sync() override;
    };

    class OCursedStream : public ostringstream
    {
    private:
        CursedBuffer buf;

    public:
        OCursedStream(Window *win, int starty, int startx, int x_buffer = 0);

    };
}

#endif //A_STRESSFUL_MACHINE_OCURSEDSTREAM_H
