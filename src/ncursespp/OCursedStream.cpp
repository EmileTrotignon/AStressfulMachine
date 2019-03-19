//
// Created by emile on 18/03/19.
//

#include <assert.h>
#include <fstream>
#include "OCursedStream.h"

namespace ncursespp
{
    ofstream log("log");

    CursedBuffer::CursedBuffer(ostream &sink, size_t buffsize, Window *window_, int starty_, int startx_, int x_buffer_)
            :
            streambuf(),
            window(window_),
            startx(startx_),
            starty(starty_),
            x_buffer(x_buffer_),
            current_y(starty),
            current_x(startx),
            sink_(sink),
            buffer_(buffsize + 1)
    {
        sink_.clear();
        char *base = &buffer_.front();
        setp(base, base + buffer_.size() - 1);
    }

    bool CursedBuffer::print_to_win()
    {
        string s;
        char *e = pptr();
        for (char *p = pbase(); p != e; p++)
        {
            s.push_back(*p);
        }

        log << s + " " << current_y << " " << current_x << " " << x_buffer << endl;
        window->mvprintstr(current_y, current_x, s, x_buffer);

        ptrdiff_t n = pptr() - pbase();
        pbump((int) -n);

        sink_.write(pbase(), n);
        return true;
    }

    CursedBuffer::int_type CursedBuffer::overflow(CursedBuffer::int_type ch)
    {
        if (sink_ && ch != traits_type::eof())
        {
            assert(less_equal<>()(pptr(), epptr()));
            *pptr() = (char) ch;
            pbump(1);
            print_to_win();
            current_x = window->get_x();
            current_y = window->get_y();
            return ch;
        }

        return traits_type::eof();

    }

/*
    streamsize CursedBuffer::xsputn(const char *s, streamsize count)
    {

        window->mvprintstr(current_y, current_x, string(s), x_buffer);
        current_x = window->get_x();
        current_y = window->get_y();
        return streambuf::xsputn(s, count);
    }*/

    int CursedBuffer::sync()
    {
        print_to_win();
        window->refresh_();
        return print_to_win() ? 0 : 1;
    }


    OCursedStream::OCursedStream(ncursespp::Window *win, int starty, int startx, int x_buffer) :
            basic_ostream<char>(&buf),
            buf(*this, 255, win, starty, startx, x_buffer)
    {

    }
}
