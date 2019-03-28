//
// Created by marcel on 25/03/19.
//

#ifndef A_STRESSFUL_MACHINE_GUIWINDOWGAMEPLAY_H
#define A_STRESSFUL_MACHINE_GUIWINDOWGAMEPLAY_H

#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QTextEdit>
#include <QFont>
#include <QTextBrowser>
#include <QVBoxLayout>

class GUIGameplay : public QWidget
{
    // Initialize macro for qt
    Q_OBJECT

public:
    explicit GUIGameplay(QWidget *parent = nullptr);

private:
    QGridLayout *windowLayout;
    QVBoxLayout *typingFieldLayout;
    QLabel *typingFieldLabel;
    QTextEdit *typingField;
    QTextBrowser *instructionView;
    QFont displayFont;
};


#endif //A_STRESSFUL_MACHINE_GUIWINDOWGAMEPLAY_H
