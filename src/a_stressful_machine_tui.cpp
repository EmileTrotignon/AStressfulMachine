//
// Created by emile on 10/03/19.
//

#include "GameTUI.h"

int main()
{
    GameTUI game("data/saves", "data/gamefiles");
    cout << "coucou" << endl;
    game.play();
    return 0;
}