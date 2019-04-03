#include "../GUI/GameGUI.h"
#include <QApplication>

int main(int argc, char ** argv)
{
    GameGUI game("data/saves", "data/gamefiles");
    return game.play(argc, argv);
}