//
// Created by emile on 15/03/19.
//

#include "Field.h"

namespace ncursespp
{
    Field::Field(int validate_key_, int height_, int width_, int starty_, int startx_,
                                           bool boxing_) :
            Window(height_, width_, starty_, startx_, boxing_),
            typing_cursor_x(0),
            typing_pos_y(0),
            validate_key(validate_key_)
    {
        keypad_on();
        typed_text = String2D();
        typed_text.push_back("");
        typing_cursor_y = typed_text.begin();
    }

    void Field::type()
    {
        curs_set(1);
        refresh_();
        int ch;
        while ((ch = getch_()) != validate_key)
        {
            switch (ch)
            {
                case KEY_RIGHT:
                    if (typing_cursor_x < (*typing_cursor_y).size())
                    {
                        typing_cursor_x++;
                    } else if (typing_cursor_y != --typed_text.end())
                    {
                        typing_cursor_y++;
                        typing_pos_y++;
                        typing_cursor_x = 0;
                    }
                    break;

                case KEY_LEFT:
                    if (typing_cursor_x > 0)
                    {
                        typing_cursor_x--;
                    } else if (typing_cursor_y != typed_text.begin())
                    {
                        typing_cursor_y--;
                        typing_pos_y--;
                        typing_cursor_x = (*typing_cursor_y).size();
                    }
                    break;

                case KEY_BACKSPACE:
                    if (typing_cursor_x != 0)
                    {
                        (*typing_cursor_y).erase(typing_cursor_x - 1, 1);
                        typing_cursor_x--;
                    } else if (typing_cursor_y != typed_text.begin() &&
                               (*typing_cursor_y).size() + (*(--typing_cursor_y)).size() < get_width())
                    {
                        auto eraser = ++typing_cursor_y;
                        typing_cursor_y--;
                        typing_pos_y--;
                        string buff = (*eraser);
                        typed_text.erase(eraser);
                        (*typing_cursor_y) += buff;

                    }
                    break;

                case KEY_DC:
                    if (typing_cursor_x != (*typing_cursor_y).size())
                    {
                        (*typing_cursor_y).erase(typing_cursor_x, 1);
                    } // Todo : add an else if clause here for multiline support
                    break;

                case '\n':
                    if (typed_text.size() < get_height())
                    {
                        typing_cursor_y++;
                        typed_text.insert(typing_cursor_y, "");
                        typing_cursor_y--;
                        typing_pos_y++;
                        typing_cursor_x = 0;
                    }
                    break;

                default:
                    if (isprint(ch) && typing_cursor_x < get_width())
                    {
                        //if (cursor_x - typed_text.begin() > 15) getch();

                        //if (cursor_x - typed_text.begin() >= typed_text.capacity()) typed_text.resize(typed_text.capacity() * 2);
                        (*typing_cursor_y).insert((*typing_cursor_y).begin() + typing_cursor_x, (char) ch);

                        //if (cursor_x - typed_text.begin() > 15) getch();
                        typing_cursor_x++;
                    }
                    break;

            }
            clear();
            mvprintstr(0, 0, string(typed_text), 0);
            refresh_();
            move_cursor((int) typing_pos_y, (int) typing_cursor_x);
        }
        curs_set(0);
        refresh_();
    }

    string Field::get_typed_text()
    {
        return string(typed_text);
    }


}


