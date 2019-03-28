//
// Created by emile on 06/03/19.
//

#include "GameGUI.h"

#include <iostream>

GameGUI::GameGUI(const string &saves_dir_, const string &gamefiles_dir_) : Game(saves_dir_, gamefiles_dir_)
{
    std::cout << "Constructing GameGUI" << std::endl;
}

int GameGUI::play(int argc, char **argv)
{
    // Creates the process
    QApplication app(argc, argv);
    std::cout << "Created app" << std::endl;
    //GUIWindowMainMenu mainMenu;
    //mainMenu.show();

    GUIWindow gameWindow;
    gameWindow.show();

    return app.exec();


}

void GameGUI::play()
{
    char myChar = 'a';
    char *myCharStar = &myChar;
    char **defaultString = &myCharStar;
    GameGUI::play(1, defaultString);
}
/*
void GameGUI::createGameplayWindow()
{

}*/