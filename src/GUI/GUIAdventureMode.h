//
// Created by emile on 09/04/19.
//

#ifndef A_STRESSFUL_MACHINE_GUIADVENTUREMODE_H
#define A_STRESSFUL_MACHINE_GUIADVENTUREMODE_H


#include <QtWidgets/QStackedWidget>
#include "GUIGameplay.h"
#include "GUIPickSave.h"
#include "GUIPickLevel.h"

class GUIAdventureMode : public QStackedWidget
{
Q_OBJECT

public:
    explicit GUIAdventureMode(GameGUI *game);

private slots:

    void pick_save();

    void pick_level();

    void launch_game();

    void return_pick_save();

private:
    GUIGameplay *game_widget;
    GUIPickSave *save_picker;
    GUIPickLevel *level_picker;
    GameGUI *game;
};


#endif //A_STRESSFUL_MACHINE_GUIADVENTUREMODE_H