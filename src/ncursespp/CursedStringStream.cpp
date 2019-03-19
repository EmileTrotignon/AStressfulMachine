//
// Created by emile on 19/03/19.
//

#include "CursedStringStream.h"

namespace ncursespp
{
    CursedStringBuffer::CursedStringBuffer(ncursespp::Window *window_, int starty_, int startx_, int x_buffer_) :
            stringbuf(), window(window_), starty(starty_), startx(startx_), x_buffer(x_buffer_)
    {

    }

    CursedStringBuffer::int_type CursedStringBuffer::overflow(CursedStringBuffer::int_type ch)
    {
        print_to_win(ch);
        current_x = window->get_x();
        current_y = window->get_y();
        return stringbuf::overflow(ch);
    }

    int CursedStringBuffer::sync()
    {
        print_to_win();
        window->refresh_();
        return stringbuf::sync();
    }

    void CursedStringBuffer::print_to_win(CursedStringBuffer::int_type ch)
    {
        string s;
        char *e = pptr();
        for (char *p = pbase(); p != e; p++)
        {
            s.push_back(*p);
        }
        if (ch != -1) s.push_back(char(ch));


        //log << s + " " << current_y << " " << current_x << " " << x_buffer << endl;
        window->mvprintstr(current_y, current_x, s, x_buffer);
    }

    CursedStringStream::CursedStringStream(ncursespp::Window *window_, int starty_, int startx_, int x_buffer_) :
            buf(window_, starty_, startx_, x_buffer_),
            stringstream()
    {
        this->init(&buf);
    }

}