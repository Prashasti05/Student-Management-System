#ifndef SEARCHSTUDENTDIALOG_H
#define SEARCHSTUDENTDIALOG_H

#include <QDialog>                //class will inherit from it, making it a dialog box
#include<QVector>                 //Qt container used to hold a list of Student
#include"student.h"


namespace Ui {
class searchstudentDialog;
}

class searchstudentDialog : public QDialog   //searchstudentDialog, which inherits from QDialog.
{
    Q_OBJECT

public:                       //Constructor: Takes a reference to a list of Student objects (students) and parent widget.
    explicit searchstudentDialog( const QVector<Student> &students, QWidget *parent = nullptr);
    ~searchstudentDialog();


private slots:

    void on_btnSearch_clicked();

private:
    Ui::searchstudentDialog *ui;
    QVector<Student>studentList;          //it is a editable copy of students vector

};

#endif // SEARCHSTUDENTDIALOG_H


  // const QVector<Student> &students---> is a book on which can not write but  only read
// whereas studentList is a photocopy on ehich u can write
//studentList(students): you're explicitly copying that list into your class's


  //QVector<Student>--> A Qt container (like a dynamic array or list) that holds Student objects
//&--->	A reference, meaning you're referring to an existing vector, not making a copy
// const--->	You promise not to modify the vector or its contents
// students--->	The name of the variable (
