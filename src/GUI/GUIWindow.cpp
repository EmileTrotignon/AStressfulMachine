//
// Created by marcel on 28/03/19.
//

#include "GUIWindow.h"

GUIWindow::GUIWindow(QWidget *parent) : QStackedWidget(parent)
{
    setObjectName("GUIWindow");
    setWindowTitle("A Stressful Machine");

    // Create the tree windows
    mainMenuWidget = new GUIMainMenu(this);
    gameplayWidget = new GUIGameplay(this);
    sandbox = new GUISandbox(this);

    // Add them to the stack
    addWidget(mainMenuWidget);
    addWidget(gameplayWidget);
    addWidget(sandbox);
    
    setCurrentWidget(mainMenuWidget);
}

// Used in GUIMainMenu
void GUIWindow::create_new_game_window()
{
    setCurrentWidget(gameplayWidget);
}

void GUIWindow::open_sandbox()
{
    setCurrentWidget(sandbox);
}
