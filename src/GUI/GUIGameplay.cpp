//
// Created by marcel on 25/03/19.
//

#include "GUIGameplay.h"

GUIGameplay::GUIGameplay(QWidget *parent) : QWidget(parent)
{
    this->setObjectName("gameplayWindow");
    this->setWindowTitle("A Stressful Machine");

    // Create font
    displayFont.setFamily("helvetica");
    displayFont.setPointSize(20);

    // Create Window Layout
    windowLayout = new QGridLayout(this);

    // Create typing field
    typingFieldLayout = new QVBoxLayout;
    typingFieldLabel = new QLabel(this);
    typingFieldLabel->setText("Write your program here");
    typingFieldLabel->setAlignment(Qt::AlignVCenter);
    typingFieldLabel->setFont(displayFont);
    typingFieldLayout->addWidget(typingFieldLabel);
    typingField = new QTextEdit(this);
    typingFieldLayout->addWidget(typingField);

    windowLayout->addLayout(typingFieldLayout, 0, 1);

    // Create instruction viewer
    instructionView = new QTextBrowser(this);
    instructionView->setText("Level instructions show up here");

    windowLayout->addWidget(instructionView, 0, 0);

}