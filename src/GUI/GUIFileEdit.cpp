#include <utility>

#include <utility>

#include <utility>
#include <file_utilities.h>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QLineEdit>

//
// Created by emile on 23/04/19.
//

#include "GUIFileEdit.h"

using namespace std;

GUIFileEdit::GUIFileEdit(fs::path file_path_, QWidget *parent) : QTextEdit(parent)
{
    open(std::move(file_path_));
}

GUIFileEdit::GUIFileEdit(QWidget *parent) : QTextEdit(parent), file_path("")
{

}

void GUIFileEdit::save()
{
    if (file_path != "") string_to_file(toPlainText().toStdString(), file_path);
    else
    {
        QString filename = QFileDialog::getSaveFileName(this, "Choose filename");
        if (!filename.isEmpty() && !filename.isNull())
        {
            file_path = filename.toStdString();
            save();
        }
    }
}

void GUIFileEdit::open(fs::path file_path_)
{
    file_path = std::move(file_path_);
    insertPlainText(QString::fromStdString(file_to_string(file_path)));
}

bool GUIFileEdit::has_file_path()
{
    return file_path != "";
}

void GUIFileEdit::save_as()
{
    file_path = (QFileDialog::getOpenFileName(this, "Choose filename")).toStdString();
    save();
}
