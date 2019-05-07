#include "GameGUI.h"
#include <QApplication>

/*
 * This main launches the GUI
 */

int main(int argc, char ** argv)
{

    // Creates the process
    QApplication app(argc, argv);
    //std::cout << "Created app" << std::endl;
    //GUIWindowMainMenu mainMenu;
    //mainMenu.show();

    GameGUI game("../data");
    game.play();

    return QApplication::exec();
}