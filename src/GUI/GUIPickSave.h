//
// Created by emile on 08/04/19.
//

#ifndef A_STRESSFUL_MACHINE_GUIPICKSAVE_H
#define A_STRESSFUL_MACHINE_GUIPICKSAVE_H


#include <QtWidgets/QWidget>
#include <QtWidgets/QListWidget>

class GameGUI;

class GUIPickSave : public QWidget
{
Q_OBJECT
public:
    explicit GUIPickSave(QWidget *parent_, GameGUI *game);

private:
    QListWidget *saves_list;
    GameGUI *game;

signals:

    void saved_picked(QString);

};


#endif //A_STRESSFUL_MACHINE_GUIPICKSAVE_H
