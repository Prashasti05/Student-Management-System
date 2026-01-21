#ifndef SEARCHSTUDENTDIALOG_H
#define SEARCHSTUDENTDIALOG_H

#include <QDialog>                
#include<QVector>                
#include"student.h"


namespace Ui {
class searchstudentDialog;
}

class searchstudentDialog : public QDialog   
{
    Q_OBJECT

public:                       
    explicit searchstudentDialog( const QVector<Student> &students, QWidget *parent = nullptr);
    ~searchstudentDialog();


private slots:

    void on_btnSearch_clicked();

private:
    Ui::searchstudentDialog *ui;
    QVector<Student>studentList;          //it is a editable copy of students vector

};

#endif // SEARCHSTUDENTDIALOG_H


