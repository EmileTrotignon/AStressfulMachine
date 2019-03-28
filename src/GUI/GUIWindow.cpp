//
// Created by marcel on 28/03/19.
//

#include "GUIWindow.h"

GUIWindow::GUIWindow(QWidget *parent) : QStackedWidget(parent)
{
    setObjectName("GUIWindow");
    setWindowTitle("A Stressful Machine");
    
    // Create the two windows
    mainMenuWidget = new GUIMainMenu(this);
    gameplayWidget = new GUIGameplay(this);

    // Add them to the stack
    addWidget(mainMenuWidget);
    addWidget(gameplayWidget);
    
    setCurrentWidget(mainMenuWidget);
}

// Used in GUIMainMenu
void GUIWindow::createNewGameWindow()
{
    setCurrentWidget(gameplayWidget);
}
