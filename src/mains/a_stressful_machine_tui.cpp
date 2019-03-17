//
// Created by emile on 10/03/19.
//

#include "../TUI/GameTUI.h"

int main()
{
    GameTUI game("data/saves", "data/gamefiles");
    game.play();
    return 0;
}