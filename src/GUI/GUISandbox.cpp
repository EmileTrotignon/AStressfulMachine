//
// Created by emile on 28/03/19.
//

#include <VirtualMachine.h>
#include <fstream>
#include <thread>
#include <QtCore/QEventLoop>
#include <sys/socket.h>
#include "GUISandbox.h"

ofstream logg("log");

void raw_vm_callback(VirtualMachine *vm, GUISandbox *sandbox)
{
    QTextCharFormat format;
    QTextCharFormat old_format = sandbox->typing_field->currentCharFormat();
    format.setForeground(QBrush(QColor("black")));
    format.setBackground(QBrush(QColor("green")));

    sandbox->typing_field->clear();
    sandbox->typing_field->textCursor().setPosition(QTextCursor::Start);

    string program = vm->get_program();
    string::iterator current_operator = vm->get_current_operator() - vm->get_program().begin() + program.begin();
    string first_half(program.begin(), current_operator);
    string operator_str(1, *current_operator);
    string second_half(current_operator + 1, program.end());

    logg << first_half << endl << operator_str << endl << second_half << endl;

    sandbox->typing_field->insertPlainText(QString::fromStdString(first_half));
    sandbox->typing_field->setCurrentCharFormat(format);
    sandbox->typing_field->insertPlainText(QString::fromStdString(operator_str));
    sandbox->typing_field->setCurrentCharFormat(old_format);
    sandbox->typing_field->insertPlainText(QString::fromStdString(second_half));


    QEventLoop loop;
    GUISandbox::connect(sandbox->next_operation_button, SIGNAL(clicked(bool)), &loop, SLOT(quit()));
    loop.exec();
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

    next_operation_button = new QPushButton("Next", this);

    stop_button = new QPushButton("Stop");

    pause_button = new QPushButton("Pause");


    // Add Widget to layout

    io_fields_layout->addWidget(vm_input_field);
    io_fields_layout->addWidget(vm_output);

    button_layout->addWidget(stop_button);
    button_layout->addWidget(pause_button);
    button_layout->addWidget(run_button);
    button_layout->addWidget(next_operation_button);


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
    function<void(VirtualMachine *)> vm_callback = bind(function(raw_vm_callback), _1, this);
    function<void(int)> vm_output_callback = bind(function(raw_vm_output_callback), _1, vm_output);


    istringstream input(vm_input_field->toPlainText().toStdString());
    ostringstream output("");
    VirtualMachine vm(typing_field->toPlainText().toStdString(), &input, &output, {}, vm_output_callback);
    vm.loop(vm_callback);
}
