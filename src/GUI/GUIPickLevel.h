//
// Created by emile on 09/04/19.
//

#ifndef A_STRESSFUL_MACHINE_GUIPICKLEVEL_H
#define A_STRESSFUL_MACHINE_GUIPICKLEVEL_H


#include <QtWidgets/QWidget>
#include <QtWidgets/QListWidget>

class GameGUI;

class GUIPickLevel : public QWidget
{
Q_OBJECT
public :
    explicit GUIPickLevel(QWidget *parent, GameGUI *game);

private:
    QListWidget *levels_list;
    GameGUI *game;

public slots:

    void pick_level(QListWidgetItem *w);

signals:

    void level_picked();
};


#endif //A_STRESSFUL_MACHINE_GUIPICKLEVEL_H
