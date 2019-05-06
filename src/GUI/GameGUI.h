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


class GameGUI : public QMainWindow, public Game
{
Q_OBJECT

private:
    GUISandbox *sandbox;
    GUIMainMenu *main_menu_widget;
    GUIAdventureMode *adventure_mode_widget;
    fs::path data_dir;

public:
    // GameGUI();
    /**
     * @param data_dir The path to the directory where the data (saves, gamefiles and assets) is
     */
    explicit GameGUI(const fs::path &data_dir);

    /* This is only implemented to ensure project compiles
     * (GameGUI is a virtual class and requires inherited virtual functions to be implemented)
     */

    /**
     * To start the execution
     */
    void play() override;

    friend GUIPickSave;
    friend GUIPickLevel;
    friend GUIGameplay;

protected slots:

    // Used in GUIMainMenu

    /**
     * Allocate a new adventure mode widget and make it the central widget
     */
    void open_adventure_mode();


    /**
     * Allocate a new sandbox mode widget and make it the central widget
     */
    void open_sandbox();

    void return_main_menu_from_pick_save();

    // Slots for escape menu
    void open_esc_dialog();

    void close_esc_dialog();

    void esc_dialog_quit();

signals:
    void resume_game(int dialog_rejected = QDialog::Rejected);

};


#endif //A_STRESSFUL_MACHINE_GAMEGUI_H
