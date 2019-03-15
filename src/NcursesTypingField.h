//
// Created by emile on 15/03/19.
//

#ifndef A_STRESSFUL_MACHINE_NCURSESTYPINGFIELD_H
#define A_STRESSFUL_MACHINE_NCURSESTYPINGFIELD_H

#include "NcursesWindow.h"
#include "String2D.h"

namespace ncursespp
{
    class NcursesTypingField : public NcursesWindow
    {
    private:
        String2D typed_text;
        size_t typing_cursor_x;
        String2D::iterator typing_cursor_y;
        size_t typing_pos_y;
        int validate_key;
    public:

        NcursesTypingField(int validate_key, int height, int width, int starty, int startx, bool boxing = false);

        void type();

        string get_typed_text();
    };
}

#endif //A_STRESSFUL_MACHINE_NCURSESTYPINGFIELD_H
