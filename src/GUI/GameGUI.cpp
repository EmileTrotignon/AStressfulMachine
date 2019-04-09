//
// Created by emile on 06/03/19.
//

#include "GameGUI.h"

#include <iostream>

GameGUI::GameGUI(const string &saves_dir_, const string &gamefiles_dir_) : QStackedWidget(nullptr),
                                                                           Game(saves_dir_, gamefiles_dir_)
{
    std::cout << "Constructing GameGUI" << std::endl;
    setObjectName("GUIWindow");
    setWindowTitle("A Stressful Machine");

    // Create the tree windows
    main_menu_widget = new GUIMainMenu(this);
    adventure_mode_widget = new GUIAdventureMode(this, this);
    sandbox = new GUISandbox(this);

    // Add them to the stack
    addWidget(main_menu_widget);
    addWidget(adventure_mode_widget);
    addWidget(sandbox);

    setCurrentWidget(main_menu_widget);
}


void GameGUI::play()
{
    show();
}

void GameGUI::open_adventure_mode()
{
    setCurrentWidget(adventure_mode_widget);
}

void GameGUI::open_sandbox()
{
    setCurrentWidget(sandbox);
}