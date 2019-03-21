//
// Created by emile on 21/03/19.
//

#ifndef A_STRESSFUL_MACHINE_MESSAGESTACK_H
#define A_STRESSFUL_MACHINE_MESSAGESTACK_H


namespace ncursespp
{
    class Window;

    class MessageStack : public Window
    {
    private:

        int xpadding;
        int ypadding;

        vector<string> messages;

    public:
        MessageStack(int height, int width, int starty, int startx, bool boxing = false, int ypadding = 0,
                     int xpadding = 0);

        void push_message(string message);

        void refresh_() override;
    };
}

#endif //A_STRESSFUL_MACHINE_MESSAGESTACK_H
