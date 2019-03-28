//
// Created by emile on 06/03/19.
//

#ifndef A_STRESSFUL_MACHINE_GAMEGUI_H
#define A_STRESSFUL_MACHINE_GAMEGUI_H

#include "../game_logic/Game.h"
#include "GUIWindow.h"

#include <QApplication>

class GameGUI : public Game
{
private:
    // Game *game;
    // GUIWindow gameWindow;
public:
    // GameGUI();
    GameGUI(const string &saves_dir, const string &gamefiles_dir);

    int play(int argc, char ** argv);

    /* This is only implemented to ensure project compiles
     * (GameGUI is a virtual class and requires inherited virtual functions to be implemented)
     */
    void play() override;
};


#endif //A_STRESSFUL_MACHINE_GAMEGUI_H
