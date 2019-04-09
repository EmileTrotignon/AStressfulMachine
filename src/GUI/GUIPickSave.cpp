//
// Created by emile on 08/04/19.
//

#include "GUIPickSave.h"
#include "GameGUI.h"

GUIPickSave::GUIPickSave(QWidget *parent_, GameGUI *game_) : QWidget(parent_), game(game_)
{

    saves_list = new QListWidget(this);
    vector<string> saves = game->save_picker->get_saves();
    for (const string &s:saves)
    {
        new QListWidgetItem(QString::fromStdString(s), saves_list);
    }

    connect(saves_list,
            SIGNAL(itemActivated(QListWidgetItem * )),
            this,
            SLOT(pick_save(QListWidgetItem * )));
}

void GUIPickSave::pick_save(QListWidgetItem *w)
{
    game->game_sequence = new GameSequence(game->save_picker->select_save(w->text().toStdString()));
    emit save_picked();
}
