#include <utility>

//
// Created by emile on 28/03/19.
//

#include <fstream>
#include <thread>
#include <QtCore/QEventLoop>
#include <QTimer>
#include <QSound>
#include <QStyle>
#include <QtWidgets/QMessageBox>
#include <QDebug>
#include <QtWidgets/QFileDialog>
#include <QApplication>

#include "VirtualMachine.h"
#include "GUISandbox.h"
#include "GUIFileEdit.h"

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

void GUISandbox::raw_vm_callback(VirtualMachine *vm)
{
    QTextCharFormat format;
    QTextCharFormat old_format = ((QTextEdit *) typing_tabs->currentWidget())->currentCharFormat();
    format.setForeground(QBrush(QColor("black")));
    format.setBackground(QBrush(QColor("green")));

    ((QTextEdit *) typing_tabs->currentWidget())->clear();

    string program = vm->get_program();
    string::iterator current_operator = vm->get_current_operator() - vm->get_program().begin() + program.begin();
    string first_half(program.begin(), current_operator);
    string operator_str(1, *current_operator);
    string second_half(current_operator + 1, program.end());

    ((QTextEdit *) typing_tabs->currentWidget())->insertPlainText(QString::fromStdString(first_half));
    ((QTextEdit *) typing_tabs->currentWidget())->setCurrentCharFormat(format);
    ((QTextEdit *) typing_tabs->currentWidget())->insertPlainText(QString::fromStdString(operator_str));
    ((QTextEdit *) typing_tabs->currentWidget())->setCurrentCharFormat(old_format);
    ((QTextEdit *) typing_tabs->currentWidget())->insertPlainText(QString::fromStdString(second_half));

    print_memory(vm, vm_memory_printer);

    if (speed_slider->value() == 0)
    {
        next_operation_button->setEnabled(true);

        QEventLoop loop;
        GUISandbox::connect(next_operation_button, SIGNAL(clicked(bool)), &loop, SLOT(quit()));
        loop.exec();
        next_operation_button->setEnabled(false);
    } else if (speed_slider->value() < GUISandbox::max_speed)
    {
        QTimer timer(nullptr);
        QEventLoop loop;

        timer.start(500 / speed_slider->value());
        QWidget::connect(&timer, SIGNAL(timeout()), &loop, SLOT(quit()));
        loop.exec();
    }
}

void GUISandbox::raw_vm_output_callback(int output)
{
    vm_output->append(QString::number(output));
}

GUISandbox::GUISandbox(fs::path assets_, QWidget *parent_) : QWidget(parent_),
                                                             assets(std::move(assets_)),
                                                             about_to_close(false)
{
    this->setObjectName("GUISandbox");
    this->setWindowTitle("A Stressful Machine");


    // Create fonts

    label_font.setFamily("Monospace");
    label_font.setPointSize(10);
    field_font = QFont("Monospace");
    field_font.setStyleHint(QFont::TypeWriter); // For portability
    field_font.setPointSize(12);

    menu_bar = new QMenuBar(this);

    file_menu = new QMenu("File", menu_bar);

    new_tab_action = new QAction("New tab");
    save_file_action = new QAction("Save", file_menu);
    save_as_file_action = new QAction("Save as", file_menu);
    open_file_action = new QAction("Open", file_menu);

    fill_menu_bar();

    // Create layouts

    window_layout = new QHBoxLayout(this);
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


    // Create tabs

    typing_tabs = new QTabWidget(this);
    typing_tabs->setDocumentMode(true);
    typing_tabs->setTabsClosable(true);
    connect(typing_tabs, SIGNAL(tabCloseRequested(int)), this, SLOT(close_tab(int)));

    // Create typing fields

    auto text_edit = new GUIFileEdit(this);
    text_edit->setFont(field_font);
    //typing_zone_layout->addWidget(text_edit, 4);
    typing_tabs->addTab(text_edit, "new_file");
    typing_tabs->currentWidget()->setFocus();
    //typing_field = new QTextEdit(this);
    message_field = new QTextEdit(this);
    message_field->setReadOnly(true);

    vm_input_field = new QTextEdit(this);

    vm_memory_printer = new QTextEdit(this);
    vm_memory_printer->setReadOnly(true);

    vm_output = new QTextEdit(this);
    vm_output->setReadOnly(true);



    // Create buttons

    run_button = new QPushButton("Run", this);


    //QIcon *icon_test = new QIcon("../data/assets/icons/icons.png");

    //run_button->setIcon(*icon_test);
    cout << (assets / "icons/jouer.png") << endl;
    run_button->setIcon(QIcon(QString::fromStdString((assets / "icons/jouer.png").string())));

    connect(run_button, SIGNAL(clicked(bool)), this, SLOT(run_code()));

    next_operation_button = new QPushButton("Next", this);
    next_operation_button->setIcon(QIcon(QString::fromStdString((assets / "icons/avancer.png").string())));
    next_operation_button->setEnabled(false);

    stop_button = new QPushButton("Stop");
    stop_button->setIcon(QIcon(QString::fromStdString((assets / "icons/arreter.png").string())));
    stop_button->setEnabled(false);


    // Create slider

    speed_slider = new QSlider(Qt::Horizontal, this);
    speed_slider->setMaximum(GUISandbox::max_speed);

    // Add fonts to widgets

    typing_field_label->setFont(label_font);
    message_label->setFont(label_font);
    input_label->setFont(label_font);
    memory_label->setFont(label_font);
    output_label->setFont(label_font);

    vm_input_field->setFont(field_font);
    vm_memory_printer->setFont(field_font);
    vm_output->setFont(field_font);
    message_field->setFont(field_font);

    place_widgets_on_layout();

    connect(qApp, SIGNAL(aboutToQuit()), this, SLOT(is_about_to_close()));
}

void GUISandbox::place_widgets_on_layout()
{

// Add Widget to layout

    io_fields_layout->addWidget(input_label);
    io_fields_layout->addWidget(vm_input_field);
    io_fields_layout->addWidget(output_label);
    io_fields_layout->addWidget(vm_output);
    io_fields_layout->addWidget(memory_label);
    io_fields_layout->addWidget(vm_memory_printer);

    button_layout->addWidget(stop_button);
    button_layout->addWidget(run_button);
    button_layout->addWidget(speed_slider, 1);
    button_layout->addWidget(next_operation_button);


    typing_zone_layout->addWidget(typing_field_label);
    typing_zone_layout->addWidget(typing_tabs, 4);
    typing_zone_layout->addWidget(message_label);
    typing_zone_layout->addWidget(message_field, 1);


    // Add sublayout to layout

    typing_zone_layout->addLayout(button_layout);
    window_layout->addLayout(typing_zone_layout);
    window_layout->addLayout(io_fields_layout);

    ((QMainWindow *) parent())->setMenuBar(menu_bar);
}

void GUISandbox::fill_menu_bar()
{
    // Create menu bar and menus


    // File menu
    new_tab_action->setShortcut(Qt::CTRL + Qt::Key_T);
    connect(new_tab_action, SIGNAL(triggered()), this, SLOT(new_tab()));

    save_file_action->setShortcut(QKeySequence::Save);
    connect(save_file_action, SIGNAL(triggered()), this, SLOT(save_file()));

    save_as_file_action->setShortcut(QKeySequence::SaveAs);
    connect(save_as_file_action, SIGNAL(triggered()), this, SLOT(save_as_file()));

    open_file_action->setShortcut(QKeySequence::Open);
    connect(open_file_action, SIGNAL(triggered()), this, SLOT(open_file()));

    // Add actions to menu

    file_menu->addAction(new_tab_action);
    file_menu->addAction(save_file_action);
    file_menu->addAction(save_as_file_action);
    file_menu->addAction(open_file_action);

    // Add menu to menu bar

    menu_bar->addMenu(file_menu);
}

void GUISandbox::run_code_prep()
{
    for (int i = 0; i < typing_tabs->count(); i++)
    {
        if (i != typing_tabs->currentIndex())
        {
            typing_tabs->setEnabled(false);
        }
    }
    ((QTextEdit *) typing_tabs->currentWidget())->setReadOnly(true);


    vm_output->clear();
    run_button->setEnabled(false);
    next_operation_button->setEnabled(false);

    if (((QTextEdit *) typing_tabs->currentWidget())->toPlainText() == "MPSI JP")
    {
        auto gg = new QMessageBox(this);
        gg->setText("  ~~-*x_XxX_x*-~~    J  P    G  A  N  G    D  A  B    D  A  B     ~~-*x_XxX_x*-~~  ");
        gg->exec();
        ((QTextEdit *) typing_tabs->currentWidget())->setText("Meilleure prepa lyonnaise a l'ouest des lazos");
    }
}

void GUISandbox::run_code()
{
    run_code_prep();

    using namespace std::placeholders;
    const function<void(VirtualMachine *)> vm_callback = bind(&GUISandbox::raw_vm_callback, this, _1);
    function<void(int)> vm_output_callback = bind(&GUISandbox::raw_vm_output_callback, this, _1);

    istringstream input(vm_input_field->toPlainText().toStdString());
    ostringstream output("");
    VirtualMachine vm(((QTextEdit *) typing_tabs->currentWidget())->toPlainText().toStdString(), &input, &output, {},
                      vm_output_callback);

    try
    {
        vm.loop(vm_callback);
    } catch (const VirtualMachineException &e)
    {
        message_field->append("Error : " + QString::fromStdString(e.what()));
    }
    message_field->append(
            QString::fromStdString("The execution is finished. Number of steps : " + to_string(vm.get_n_steps())));

    run_code_finish();

    ((QTextEdit *) typing_tabs->currentWidget())->insertPlainText(QString::fromStdString(vm.get_program()));
}

void GUISandbox::run_code_finish()
{
    ((QTextEdit *) typing_tabs->currentWidget())->clear();
    ((QTextEdit *) typing_tabs->currentWidget())->setReadOnly(false);

    for (int i = 0; i < typing_tabs->count(); i++)
    {
        typing_tabs->setEnabled(true);
    }
    run_button->setEnabled(true);
    next_operation_button->setEnabled(false);

}

void GUISandbox::close_tab(int index)
{
    qDebug() << "Nbre de tabs avant:" << typing_tabs->count();
    if (typing_tabs->count() >= 1) typing_tabs->removeTab(index);
    qDebug() << "Nbre de tabs apres:" << typing_tabs->count();
}

void GUISandbox::save_file()
{
    for (int i = 0; i < typing_tabs->count(); i++)
    {
        if (((GUIFileEdit *) (typing_tabs->widget(i)))->has_file_path()) // if the file has already been saved once
        {
            ((GUIFileEdit *) (typing_tabs->widget(i)))->save();
        } else if (i == typing_tabs->currentIndex())
        {
            ((GUIFileEdit *) (typing_tabs->widget(i)))->save();
            if (((GUIFileEdit *) (typing_tabs->widget(i)))->has_file_path())
            {
                typing_tabs->setTabText(i, QString::fromStdString(
                        ((GUIFileEdit *) (typing_tabs->widget(i)))->file_path.filename().string()));
            }
        }
    }
}

void GUISandbox::save_as_file()
{
    ((GUIFileEdit *) (typing_tabs->currentWidget()))->save_as();
}

void GUISandbox::open_file()
{
    QString filename = QFileDialog::getOpenFileName(this, "Choose file");
    if (!filename.isEmpty() && !filename.isNull())
    {
        fs::path p(filename.toStdString());
        auto text_edit = new GUIFileEdit(this);
        text_edit->open(p);
        typing_tabs->addTab(text_edit, QString::fromStdString(p.filename().string()));
    }

}


void GUISandbox::new_tab()
{
    auto text_edit = new GUIFileEdit(this);
    text_edit->setFont(field_font);
    typing_tabs->addTab(text_edit, "new_file");
    typing_tabs->currentWidget()->setFocus();
}

void GUISandbox::close_current_tab()
{

}

GUISandbox::~GUISandbox()
{
    if (!about_to_close)
    {
        ((QMainWindow *) window())->menuBar()->hide();
        delete ((QMainWindow *) window())->menuBar();
    }
}

void GUISandbox::is_about_to_close()
{
    about_to_close = true;
}
