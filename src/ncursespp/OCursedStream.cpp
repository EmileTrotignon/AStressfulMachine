//
// Created by emile on 18/03/19.
//

#include "OCursedStream.h"

namespace ncursespp
{


    CursedBuffer::CursedBuffer(Window *window_, int starty_, int startx_, int x_buffer_) : streambuf(),
                                                                                           window(window_),
                                                                                           startx(startx_),
                                                                                           starty(starty_),
                                                                                           x_buffer(x_buffer_),
                                                                                           current_y(starty),
                                                                                           current_x(startx)
    {

    }

    int CursedBuffer::overflow(int ch)
    {
        if (current_x >= window->get_width() - x_buffer)
        {
            current_x = startx;
            current_y++;
        } else if (ch == '\n') current_y++;
        window->mvaddch_(current_y, current_x, (chtype) ch);
        current_x++;
        return streambuf::overflow(ch);
    }

    int CursedBuffer::sync()
    {
        window->refresh_();
        return streambuf::sync();
    }


    OCursedStream::OCursedStream(ncursespp::Window *win, int starty, int startx, int x_buffer) : ostringstream(),
                                                                                                 buf(win, starty,
                                                                                                     startx, x_buffer)
    {

    }
}