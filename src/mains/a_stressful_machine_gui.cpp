#include "../GUI/GameGUI.h"
#include <QApplication>

int main(int argc, char ** argv)
{

    // Creates the process
    QApplication app(argc, argv);
    std::cout << "Created app" << std::endl;
    //GUIWindowMainMenu mainMenu;
    //mainMenu.show();

    GameGUI game("data/saves", "data/gamefiles");
    game.play();

    return QApplication::exec();
}