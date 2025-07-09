#ifndef ADDSTUDENTDIALOG_H
#define ADDSTUDENTDIALOG_H

#include <QDialog>          //includes the Qt class QDialog
#include "student.h"        //Includes header file for Student class

namespace Ui {
class AddStudentDialog;
}

class AddStudentDialog : public QDialog  //class inherited from qdialog
{
    Q_OBJECT

public:
    explicit AddStudentDialog(QWidget *parent = nullptr);
    ~AddStudentDialog();

    Student getStudent() const;   // Getter function that returns a Student object.
        // 'const' means it doesn't modify any member variables of the class.

private slots:
    void on_btnSaveStudent_clicked();

private:
    Ui::AddStudentDialog *ui;     //pointer to the UI object
};

#endif // ADDSTUDENTDIALOG_H
