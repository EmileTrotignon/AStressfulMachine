//
// Created by emile on 09/04/19.
//

#include "GUIPickLevel.h"
#include "GameGUI.h"

GUIPickLevel::GUIPickLevel(QWidget *parent_, GameGUI *game_) : QWidget(parent_), game(game_)
{

    levels_list = new QListWidget(this);
    vector<string> levels = game->game_sequence->get_available_levels();
    for (const string &s:levels)
    {
        new QListWidgetItem(QString::fromStdString(s), levels_list);
    }

    connect(levels_list,
            SIGNAL(itemActivated(QListWidgetItem * )),
            this,
            SLOT(pick_save(QListWidgetItem * )));
}

void GUIPickLevel::pick_level(QListWidgetItem *w)
{
    game->game_sequence->select_level(w->text().toStdString());
    emit level_picked();
}