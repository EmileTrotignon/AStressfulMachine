//
// Created by emile on 15/03/19.
//

#ifndef A_STRESSFUL_MACHINE_NCURSESTYPINGFIELD_H
#define A_STRESSFUL_MACHINE_NCURSESTYPINGFIELD_H

#include "Window.h"
#include "String2D.h"

namespace ncursespp
{
    class Field : public Window
    {
    private:
        String2D typed_text;
        size_t typing_cursor_x;
        String2D::iterator typing_cursor_y;
        size_t typing_pos_y;
        const vector<int> validate_keys;
        MEVENT mouse_event;
        mmask_t mouse_mask;
    public:

        Field(const vector<int> &validate_keys, int height, int width, int starty, int startx, bool boxing = false);

        int type();

        string get_typed_text();

        void set_typed_text(const string &new_text);

        void attron_char(size_t ch_index, int attr);

        void attroff_char(size_t ch_index, int attr);
    };
}

#endif //A_STRESSFUL_MACHINE_NCURSESTYPINGFIELD_H
