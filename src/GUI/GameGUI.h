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
// #include <QtWidgets/QStackedWidget>
#include <QStackedWidget>
#include <QDialog>
#include <QPushButton>
#include <QDebug>
#include <QShortcut>

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
    friend GUIGameplay;

private slots:

    // Used in GUIMainMenu
    void open_adventure_mode();
    void open_sandbox();

    void return_main_menu_from_pick_save();

    // Slots for escape menu
    void open_esc_menu();
    void esc_dlg_rejected();
    void esc_dlg_quit();

signals:
    void resume_game(int dialog_rejected = QDialog::Rejected);

};


#endif //A_STRESSFUL_MACHINE_GAMEGUI_H
