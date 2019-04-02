//
// Created by emile on 28/03/19.
//

#include <VirtualMachine.h>
#include <fstream>
#include <thread>
#include <QtCore/QEventLoop>
#include <sys/socket.h>
#include "GUISandbox.h"


void print_memory(VirtualMachine *vm, QTextEdit *memory_printer)
{
    QTextCharFormat format;
    format.setForeground(QBrush(QColor("black")));
    format.setBackground(QBrush(QColor("green")));
    QTextCharFormat old_format = memory_printer->currentCharFormat();

    memory_printer->clear();

    for (auto e = vm->get_memory().begin(); e < vm->get_memory().end(); e++)
    {
        if (e == vm->get_memory_ptr()) memory_printer->setCurrentCharFormat(format);
        QString s = QString::number(*e);
        memory_printer->insertPlainText(s);
        if (e == vm->get_memory_ptr()) memory_printer->setCurrentCharFormat(old_format);
        memory_printer->insertPlainText(" ");
    }

}

void raw_vm_callback(VirtualMachine *vm, GUISandbox *sandbox)
{
    QTextCharFormat format;
    QTextCharFormat old_format = sandbox->typing_field->currentCharFormat();
    format.setForeground(QBrush(QColor("black")));
    format.setBackground(QBrush(QColor("green")));

    sandbox->typing_field->clear();

    string program = vm->get_program();
    string::iterator current_operator = vm->get_current_operator() - vm->get_program().begin() + program.begin();
    string first_half(program.begin(), current_operator);
    string operator_str(1, *current_operator);
    string second_half(current_operator + 1, program.end());

    sandbox->typing_field->insertPlainText(QString::fromStdString(first_half));
    sandbox->typing_field->setCurrentCharFormat(format);
    sandbox->typing_field->insertPlainText(QString::fromStdString(operator_str));
    sandbox->typing_field->setCurrentCharFormat(old_format);
    sandbox->typing_field->insertPlainText(QString::fromStdString(second_half));

    print_memory(vm, sandbox->vm_memory_printer);

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


    // Create fonts

    label_font.setFamily("Monospace");
    label_font.setPointSize(10);
    field_font = QFont("Monospace");
    field_font.setStyleHint(QFont::TypeWriter); // For portability
    field_font.setPointSize(12);


    // Create menu bar and menus

    menu_bar = new QMenuBar;

    // Create layouts

    windowLayout = new QGridLayout(this);
    typing_zone_layout = new QVBoxLayout;
    button_layout = new QHBoxLayout;
    io_fields_layout = new QVBoxLayout;


    // Create labels

    typing_field_label = new QLabel(this);
    typing_field_label->setText("Code editor");
    typing_field_label->setAlignment(Qt::AlignVCenter);

    input_label = new QLabel(this);
    input_label->setText("Input editor");
    input_label->setAlignment(Qt::AlignVCenter);

    output_label = new QLabel(this);
    output_label->setText("Program output");
    output_label->setAlignment(Qt::AlignVCenter);

    memory_label = new QLabel(this);
    memory_label->setText("Internal memory state");
    memory_label->setAlignment(Qt::AlignVCenter);

    message_label = new QLabel(this);
    message_label->setText("Log");
    message_label->setAlignment(Qt::AlignVCenter);


    // Create typing fields

    typing_field = new QTextEdit(this);
    message_field = new QTextEdit(this);
    message_field->setReadOnly(true);

    vm_input_field = new QTextEdit(this);

    vm_memory_printer = new QTextEdit(this);
    vm_memory_printer->setReadOnly(true);

    vm_output = new QTextEdit(this);
    vm_output->setReadOnly(true);



    // Create buttons

    run_button = new QPushButton("Run", this);
    connect(run_button, SIGNAL(clicked(bool)), this, SLOT(run_code()));

    next_operation_button = new QPushButton("Next", this);
    next_operation_button->setEnabled(false);

    stop_button = new QPushButton("Stop");
    stop_button->setEnabled(false);

    pause_button = new QPushButton("Pause");
    pause_button->setEnabled(false);


    // Add fonts to widgets

    typing_field_label->setFont(label_font);
    message_label->setFont(label_font);
    input_label->setFont(label_font);
    memory_label->setFont(label_font);
    output_label->setFont(label_font);

    typing_field->setFont(field_font);
    vm_input_field->setFont(field_font);
    vm_memory_printer->setFont(field_font);
    vm_output->setFont(field_font);
    message_field->setFont(field_font);

    place_widgets_on_layout();
}

void GUISandbox::place_widgets_on_layout()
{
// Add Widget to layout

    io_fields_layout->addWidget(input_label);
    io_fields_layout->addWidget(vm_input_field);
    io_fields_layout->addWidget(memory_label);
    io_fields_layout->addWidget(vm_memory_printer);
    io_fields_layout->addWidget(output_label);
    io_fields_layout->addWidget(vm_output);

    button_layout->addWidget(stop_button);
    button_layout->addWidget(pause_button);
    button_layout->addWidget(run_button);
    button_layout->addWidget(next_operation_button);


    typing_zone_layout->addWidget(typing_field_label);
    typing_zone_layout->addWidget(typing_field, 4);
    typing_zone_layout->addWidget(message_label);
    typing_zone_layout->addWidget(message_field, 1);


    // Add sublayout to layout

    typing_zone_layout->addLayout(button_layout);
    windowLayout->addLayout(typing_zone_layout, 0, 0);
    windowLayout->addLayout(io_fields_layout, 0, 1);
}

void GUISandbox::run_code()
{
    typing_field->setReadOnly(true);

    using namespace std::placeholders;
    function<void(VirtualMachine *)> vm_callback = bind(function(raw_vm_callback), _1, this);
    function<void(int)> vm_output_callback = bind(function(raw_vm_output_callback), _1, vm_output);

    vm_output->clear();
    run_button->setEnabled(false);
    next_operation_button->setEnabled(true);

    istringstream input(vm_input_field->toPlainText().toStdString());
    ostringstream output("");
    VirtualMachine vm(typing_field->toPlainText().toStdString(), &input, &output, {}, vm_output_callback);
    try
    {
        vm.loop(vm_callback);
    } catch (const VirtualMachineException &e)
    {
        message_field->append("Error : " + QString::fromStdString(e.what()));
    }
    message_field->append("The execution is finished");
    typing_field->clear();
    typing_field->insertPlainText(QString::fromStdString(vm.get_program()));
    typing_field->setReadOnly(false);
    run_button->setEnabled(true);
    next_operation_button->setEnabled(false);
}
