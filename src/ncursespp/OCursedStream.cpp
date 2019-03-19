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

    void CursedBuffer::print_to_win()
    {
        string s;
        char *e = pptr();
        for (char *p = pbase(); p < e; p++)
        {
            s.push_back(*p);
        }
    }

    CursedBuffer::int_type CursedBuffer::overflow(CursedBuffer::int_type ch)
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

    streamsize CursedBuffer::xsputn(const char *s, streamsize count)
    {
        /*
        window->mvprintstr(current_y, current_x, string(s), x_buffer);
        current_x = window->get_x();
        current_y = window->get_y();*/
        return streambuf::xsputn(s, count);
    }

    int CursedBuffer::sync()
    {
        window->refresh_();
        return streambuf::sync();
    }


    OCursedStream::OCursedStream(ncursespp::Window *win, int starty, int startx, int x_buffer) :
            basic_iostream<char>(
                    &buf),
                                                                                                 buf(win, starty,
                                                                                                     startx, x_buffer)
    {

    }
}
