//
// Created by emile on 08/04/19.
//

#ifndef A_STRESSFUL_MACHINE_GUIPICKSAVE_H
#define A_STRESSFUL_MACHINE_GUIPICKSAVE_H


#include <QtWidgets/QWidget>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

class GameGUI;

using namespace std;

class GUIPickSave : public QWidget
{
Q_OBJECT
public:
    explicit GUIPickSave(QWidget *parent_, GameGUI *game);

private:
    QListWidget *saves_list;
    QVBoxLayout *layout;
    GameGUI *game;
    QPushButton *back_button;

public slots:

    void pick_save(QListWidgetItem *w);

signals:

    void save_picked();

};


#endif //A_STRESSFUL_MACHINE_GUIPICKSAVE_H
