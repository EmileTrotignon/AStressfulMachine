//
// Created by emile on 21/03/19.
//

#include "ncurses++.h"

namespace ncursespp
{
    MessageStack::MessageStack(int height_, int width_, int starty_, int startx_, bool boxing_, int ypadding_,
                               int x_padding_) :
            Window(height_, width_, starty_, startx_, boxing_), ypadding(ypadding_), xpadding(x_padding_)
    {

    }

    void MessageStack::push_message(string message)
    {
        const int w = (boxing ? width - 2 : width) - 2 * xpadding;
        if (message.find('\n') != string::npos) throw invalid_argument("Line return are forbidden in message");
        else if (message.size() > w)
            throw invalid_argument(
                    "Message should be shorter than window size (" + to_string(w) + ")." +
                    " Message : " +
                    message);

        messages.push_back(message);
    }

    void MessageStack::refresh_()
    {
        const int h = (boxing ? height - 2 : height) - 2 * ypadding;

        const int sy = ypadding + (boxing ? 1 : 0);
        const int sx = xpadding + (boxing ? 1 : 0);

        if (messages.size() <= h)
        {
            for (int i = 0; i < messages.size(); i++)
            {
                mvprintstr(sy + i, sx, messages[i]);
            }
        } else
        {
            for (int i = h - 1; i >= 0; i--)
            {
                mvprintstr(sy + i, sx, messages[messages.size() - h + i]);
            }
        }
        Window::refresh_();
    }
}