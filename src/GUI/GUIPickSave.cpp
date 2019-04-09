//
// Created by emile on 08/04/19.
//

#include "GUIPickSave.h"
#include "GameGUI.h"

GUIPickSave::GUIPickSave(QWidget *parent_, GameGUI *game_) : QWidget(parent_), game(game_)
{
    saves_list = new QListWidget(this);
    vector<string> saves = game->save_picker->get_saves();
}
