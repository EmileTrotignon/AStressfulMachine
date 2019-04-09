//
// Created by emile on 09/04/19.
//

#ifndef A_STRESSFUL_MACHINE_GUIADVENTUREMODE_H
#define A_STRESSFUL_MACHINE_GUIADVENTUREMODE_H


#include <QtWidgets/QStackedWidget>
#include "GUIGameplay.h"
#include "GUIPickSave.h"
#include "GuiPickLevel.h"

class GUIAdventureMode : public QStackedWidget
{
Q_OBJECT

public:
    explicit GUIAdventureMode(QWidget *parent, GameGUI *game);

private slots:

    void pick_save();

    void pick_level();

    void launch_game();

private:
    GUIGameplay *game_widget;
    GUIPickSave *save_picker;
    GUIPickLevel *level_picker;
};


#endif //A_STRESSFUL_MACHINE_GUIADVENTUREMODE_H
