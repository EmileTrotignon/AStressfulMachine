//
// Created by emile on 06/03/19.
//

#ifndef A_STRESSFUL_MACHINE_GAMEGUI_H
#define A_STRESSFUL_MACHINE_GAMEGUI_H

#include "../game_logic/Game.h"
#include "GUISandbox.h"
#include "GUIMainMenu.h"
#include "GUIGameplay.h"
#include "GUIAdventureMode.h"

#include <QApplication>
#include <QtWidgets/QStackedWidget>

class GUIPickSave;

class GUIPickLevel;


class GameGUI : public QStackedWidget, public Game
{
Q_OBJECT
private:
    GUISandbox *sandbox;
    GUIMainMenu *main_menu_widget;
    GUIAdventureMode *adventure_mode_widget;

public:
    // GameGUI();
    GameGUI(const string &saves_dir, const string &gamefiles_dir);

    /* This is only implemented to ensure project compiles
     * (GameGUI is a virtual class and requires inherited virtual functions to be implemented)
     */
    void play() override;

    friend GUIPickSave;
    friend GUIPickLevel;

public slots:

    // Used in GUIMainMenu
    void open_adventure_mode();

    void open_sandbox();
};


#endif //A_STRESSFUL_MACHINE_GAMEGUI_H
