//
// Created by emile on 28/03/19.
//

#include <VirtualMachine.h>
#include <fstream>
#include "GUISandbox.h"

void raw_vm_callback(VirtualMachine *vm, QTextEdit *typing_field, QTextEdit *memory_printer)
{

}

void raw_vm_output_callback(int output, QTextEdit *output_field)
{
    output_field->append(QString::number(output));
}

GUISandbox::GUISandbox(QWidget *parent) : QWidget(parent)
{
    this->setObjectName("GUISandbox");
    this->setWindowTitle("A Stressful Machine");

    // Create font
    displayFont.setFamily("arial");
    displayFont.setPointSize(20);

    // Create layouts
    windowLayout = new QGridLayout(this);
    typing_zone_layout = new QVBoxLayout;
    button_layout = new QHBoxLayout;
    io_fields_layout = new QVBoxLayout;


    // Create labels

    typing_field_label = new QLabel(this);
    typing_field_label->setText("Write your program here");
    typing_field_label->setAlignment(Qt::AlignVCenter);
    typing_field_label->setFont(displayFont);


    // Create typing fields

    typing_field = new QTextEdit(this);
    vm_input_field = new QTextEdit(this);
    vm_output = new QTextEdit(this);
    vm_output->setReadOnly(true);


    // Create buttons

    run_button = new QPushButton("Run", this);
    connect(run_button, SIGNAL(clicked(bool)), this, SLOT(run_code()));

    stop_button = new QPushButton("Stop");

    pause_button = new QPushButton("Pause");


    // Add Widget to layout

    io_fields_layout->addWidget(vm_input_field);
    io_fields_layout->addWidget(vm_output);

    button_layout->addWidget(stop_button);
    button_layout->addWidget(pause_button);
    button_layout->addWidget(run_button);


    typing_zone_layout->addWidget(typing_field_label);
    typing_zone_layout->addWidget(typing_field);


    // Add sublayout to layout

    typing_zone_layout->addLayout(button_layout);
    windowLayout->addLayout(typing_zone_layout, 0, 0);
    windowLayout->addLayout(io_fields_layout, 0, 1);

}

void GUISandbox::run_code()
{
    using namespace std::placeholders;
    function<void(VirtualMachine *)> vm_callback = bind(function(raw_vm_callback), _1, typing_field, memory_printer);
    function<void(int)> vm_output_callback = bind(function(raw_vm_output_callback), _1, vm_output);


    istringstream input(vm_input_field->toPlainText().toStdString());
    ostringstream output("");
    VirtualMachine vm(typing_field->toPlainText().toStdString(), &input, &output, {}, vm_output_callback);
    vm.loop(vm_callback);
}
