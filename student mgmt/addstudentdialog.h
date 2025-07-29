#ifndef ADDSTUDENTDIALOG_H
#define ADDSTUDENTDIALOG_H

#include <QDialog>          
#include "student.h"        

namespace Ui {
class AddStudentDialog;
}

class AddStudentDialog : public QDialog  
{
    Q_OBJECT

public:
    explicit AddStudentDialog(QWidget *parent = nullptr);
    ~AddStudentDialog();

    Student getStudent() const;   

private slots:
    void on_btnSaveStudent_clicked();

private:
    Ui::AddStudentDialog *ui;     
};

#endif // ADDSTUDENTDIALOG_H
