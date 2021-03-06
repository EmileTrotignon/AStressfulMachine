//
// Created by emile on 15/03/19.
//

#include <vector>
#include <algorithm>
#include "Field.h"

namespace ncursespp
{
    Field::Field(const vector<int> &validate_keys_, int height_, int width_, int starty_, int startx_,
                 bool boxing_) :
            Window(height_, width_, starty_, startx_, boxing_),
            typing_cursor_x(0),
            typing_pos_y(0),
            validate_keys(validate_keys_)
    {
        keypad_on();
        typed_text = String2D();
        typed_text.push_back("");
        typing_cursor_y = typed_text.begin();
    }

    int Field::type()
    {
        mousemask(mouse_mask, nullptr);
        curs_set(1);
        mvprint_multiline_str(0, 0, string(typed_text), 0);
        move_cursor((int) typing_pos_y, (int) typing_cursor_x);
        refresh_();
        int ch;
        while (find(validate_keys.begin(), validate_keys.end(), (ch = getch_())) == validate_keys.end())
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

                case KEY_UP:
                    if (typing_cursor_y != typed_text.begin())
                    {
                        typing_cursor_y--;
                        typing_pos_y--;
                        if (typing_cursor_x > (*typing_cursor_y).size()) typing_cursor_x = (*typing_cursor_y).size();
                    }
                    break;

                case KEY_DOWN:
                    if (typing_cursor_y != --(typed_text.end()))
                    {
                        typing_cursor_y++;
                        typing_pos_y++;
                        if (typing_cursor_x > (*typing_cursor_y).size()) typing_cursor_x = (*typing_cursor_y).size();
                    }
                    break;

                case KEY_BACKSPACE:
                    if (typing_cursor_x != 0)
                    {
                        (*typing_cursor_y).erase(typing_cursor_x - 1, 1);
                        typing_cursor_x--;
                    } else if (typing_cursor_y != typed_text.begin())
                    {
                        auto available_length = get_width() - 1 - (*(--typing_cursor_y)).size();
                        auto eraser = ++typing_cursor_y;
                        typing_cursor_y--;
                        typing_pos_y--;
                        string buff = (*eraser).substr(0, available_length);
                        if (available_length >= (*eraser).size()) // Both strings fit in one line
                        {
                            typed_text.erase(eraser);
                            typing_cursor_x = (*typing_cursor_y).size();
                            (*typing_cursor_y) += buff;
                        } else
                        {
                            (*eraser).erase(0, available_length);
                            typing_cursor_x = (*typing_cursor_y).size();
                            (*typing_cursor_y) += buff;
                        }
                    }
                    break;

                case KEY_DC:
                    if (typing_cursor_x != (*typing_cursor_y).size())
                    {
                        (*typing_cursor_y).erase(typing_cursor_x, 1);
                    } else if (typing_cursor_y != --(typed_text.end()))
                    {
                        auto available_length = get_width() - 1 - (*typing_cursor_y).size();
                        auto eraser = ++typing_cursor_y;
                        typing_cursor_y--;
                        // typing_pos_y;
                        string buff = (*eraser);
                        if (available_length >= (*eraser).size())
                        {
                            typed_text.erase(eraser);
                            // typing_cursor_x = (*typing_cursor_y).size();
                            (*typing_cursor_y) += buff;
                        } else
                        {
                            (*eraser).erase(0, available_length);
                            (*typing_cursor_y) += buff;
                        }
                    }
                    break;

                case '\n':
                    if (typed_text.size() < get_height())
                    {
                        string new_line = (*typing_cursor_y).substr(typing_cursor_x,(*typing_cursor_y).size());
                        (*typing_cursor_y).erase(typing_cursor_x,(*typing_cursor_y).size());
                        typing_cursor_y++;
                        typed_text.insert(typing_cursor_y, new_line);
                        typing_cursor_y--;
                        typing_pos_y++;
                        typing_cursor_x = 0;
                    }
                    break;

                case KEY_MOUSE:
                    if(getmouse(&mouse_event) == OK )
                    {
                        if(mouse_event.bstate & BUTTON1_CLICKED)
                        {
                            int* mouseX = new int(mouse_event.x);
                            int* mouseY = new int(mouse_event.y);
                            // Verify that mouse is in the typing window
                            if(wmouse_trafo(window, mouseY, mouseX, false))
                            {
                                // Verify that mouseY points to a valid position for cursor & mouseX points to a valid position for cursor
                                if (*mouseY < typed_text.size())
                                {
                                    typing_pos_y = 0;
                                    typing_cursor_y = typed_text.begin();
                                    for (int i = 0; i < *mouseY; i++)
                                    {
                                        typing_cursor_y++;
                                        typing_pos_y++;
                                    }
                                    if (*mouseX <= (*typing_cursor_y).length()) typing_cursor_x = (size_t) *mouseX;
                                    else typing_cursor_x = (*typing_cursor_y).length();
                                }
                            }
                            delete mouseX;
                            delete mouseY;
                            mouseX = nullptr;
                            mouseY = nullptr;
                        }
                    }
                    break;

                case KEY_HOME:
                    typing_cursor_x = 0;
                    break;

                case KEY_END:
                    typing_cursor_x = (*typing_cursor_y).length();
                    break;

                default:
                    if (isprint(ch))
                    {
                        if ((*typing_cursor_y).size() < get_width() -1)
                        {
                            (*typing_cursor_y).insert((*typing_cursor_y).begin() + typing_cursor_x, (char) ch);
                            typing_cursor_x++;
                        }
                        else if (typed_text.size() < get_height())
                        {
                            typing_cursor_y++;
                            string new_line;
                            new_line.push_back((char) ch);
                            typed_text.insert(typing_cursor_y, new_line);
                            typing_cursor_y--;
                            typing_pos_y++;
                            typing_cursor_x = 1;
                        }
                    }
                    /*
                    if (isprint(ch) && typing_cursor_x < get_width())
                    {
                        //if (cursor_x - typed_text.begin() > 15) getch();

                        //if (cursor_x - typed_text.begin() >= typed_text.capacity()) typed_text.resize(typed_text.capacity() * 2);
                        (*typing_cursor_y).insert((*typing_cursor_y).begin() + typing_cursor_x, (char) ch);

                        //if (cursor_x - typed_text.begin() > 15) getch();
                        typing_cursor_x++;
                    }
                     */
                    break;

            }
            erase();

            mvprint_multiline_str(0, 0, string(typed_text), 0);
            refresh_();
            move_cursor((int) typing_pos_y, (int) typing_cursor_x);
        }
        curs_set(0);
        refresh_();
        return ch;
    }

    string Field::get_typed_text()
    {
        return string(typed_text);
    }

    void Field::set_typed_text(const string &new_text)
    {
        typed_text = String2D(new_text);
        typing_cursor_y = typed_text.begin();
    }

    void Field::attron_char(size_t ch_index, int attr)
    {

        mvprint_multiline_str(0, 0, string(typed_text), 0);
        size_t i = 0;
        auto y = typed_text.begin();
        size_t y_pos = 0;
        while (y != typed_text.end())
        {
            if (i + (*y).size() < ch_index)
            {
                i += (*y).size() + 1; // + 1 to account for the '\n'
                y++;
                y_pos++;
            } else
            {
                attron_(attr);
                mvaddch_((int) y_pos, (int) (ch_index - i), (chtype) (*y)[ch_index - i]);
                attroff_(attr);
                return;
            }
        }
        throw invalid_argument("Index out of bounds");
    }

    void Field::attroff_char(size_t ch_index, int attr)
    {
        mvprint_multiline_str(0, 0, string(typed_text), 0);
        size_t i = 0;
        auto y = typed_text.begin();
        size_t y_pos = 0;
        while (y != typed_text.end())
        {
            if (i + (*y).size() < ch_index)
            {
                i += (*y).size();
                y++;
                y_pos++;
            } else
            {
                move_cursor((int) y_pos, (int) (ch_index - i));
                attroff_(attr);
                mvaddch_((int) y_pos, (int) (ch_index - i), (chtype) (*y)[ch_index - i]);
                return;
            }
        }
        throw invalid_argument("Index out of bounds");
    }
}


