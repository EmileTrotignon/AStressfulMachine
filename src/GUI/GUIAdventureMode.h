//
// Created by emile on 09/04/19.
//

#ifndef A_STRESSFUL_MACHINE_GUIADVENTUREMODE_H
#define A_STRESSFUL_MACHINE_GUIADVENTUREMODE_H


#include <QtWidgets/QStackedWidget>
#include "GUIGameplay.h"
#include "GUIPickSave.h"
#include "GUIPickLevel.h"

/**
 * @brief This widget manage the different screens of the adventure mode (aka the game)
 */
class GUIAdventureMode : public QStackedWidget
{
Q_OBJECT

public:

    explicit GUIAdventureMode(GameGUI *game);

private slots:

    /**
     * @brief Launches the game
     */
    void launch_game();

    void return_pick_save();

public slots:

    /**
     * @brief Open the dialog when escape is pressed.
     * This is a slightly modified version of GameGUI's escape dialog
     */
    void open_esc_dialog();

    /**
     * Open the save picking screen
     */
    void pick_save();

    /**
     * Open the level picking screen
     */
    void pick_level();

private:

    GUIGameplay *game_widget;
    GUIPickSave *save_picker;
    GUIPickLevel *level_picker;
    GameGUI *game;
};


#endif //A_STRESSFUL_MACHINE_GUIADVENTUREMODE_H
