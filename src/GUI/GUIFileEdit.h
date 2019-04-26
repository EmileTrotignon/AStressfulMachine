//
// Created by emile on 23/04/19.
//

#ifndef A_STRESSFUL_MACHINE_GUIFILEEDIT_H
#define A_STRESSFUL_MACHINE_GUIFILEEDIT_H


#include <QtWidgets/QTextEdit>
#include <filesystem>

using namespace std;
namespace fs = filesystem;

class GUIFileEdit : public QTextEdit
{
public:

    fs::path file_path;

    explicit GUIFileEdit(QWidget *parent = nullptr);

    explicit GUIFileEdit(fs::path file_path, QWidget *parent = nullptr);

    void save();

    void save_as();

    void open(fs::path file_path);

    bool has_file_path();
};


#endif //A_STRESSFUL_MACHINE_GUIFILEEDIT_H
