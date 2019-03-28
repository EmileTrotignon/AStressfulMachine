//
// Created by emile on 28/03/19.
//

#include "GUISandbox.h"

GUISandbox::GUISandbox(QWidget *parent) : QWidget(parent)
{
    this->setObjectName("gameplayWindow");
    this->setWindowTitle("A Stressful Machine");

    // Create font
    displayFont.setFamily("arial");
    displayFont.setPointSize(20);

    // Create Window Layout
    windowLayout = new QGridLayout(this);

    // Create typing field
    typing_zone_layout = new QVBoxLayout;
    typing_field_label = new QLabel(this);
    typing_field_label->setText("Write your program here");
    typing_field_label->setAlignment(Qt::AlignVCenter);
    typing_field_label->setFont(displayFont);
    typing_zone_layout->addWidget(typing_field_label);
    typing_field = new QTextEdit(this);
    typing_zone_layout->addWidget(typing_field);

    windowLayout->addLayout(typing_zone_layout, 0, 1);

    // Create buttons

    run_button = new QPushButton("Run", this);
    typing_zone_layout->addWidget(run_button);


}