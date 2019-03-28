//
// Created by marcel on 28/03/19.
//

#ifndef A_STRESSFUL_MACHINE_GUIWINDOW_H
#define A_STRESSFUL_MACHINE_GUIWINDOW_H

#include <QStackedWidget>
#include <QWidget>

#include "GUIGameplay.h"
#include "GUIMainMenu.h"

class GUIWindow : public QStackedWidget
{
    // Initialize qt macro
    Q_OBJECT

public:
    explicit GUIWindow(QWidget *parent = nullptr);

private slots:
    // Used in GUIMainMenu
    void createNewGameWindow();

private:
    GUIMainMenu *mainMenuWidget;
    GUIGameplay *gameplayWidget;
};


#endif //A_STRESSFUL_MACHINE_GUIWINDOW_H
