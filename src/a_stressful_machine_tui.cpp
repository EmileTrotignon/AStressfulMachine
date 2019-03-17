//
// Created by emile on 10/03/19.
//

#include "GameTUI.h"

int main()
{
    GameTUI game("data/saves", "data/gamefiles");
    cout << "## Running a_stressful_machine_tui: successfully created game" << endl;
    game.play();
    return 0;
}