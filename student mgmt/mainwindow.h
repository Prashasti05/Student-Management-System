#ifndef MAINWINDOW_H        //Header guards — prevent file from being included more than once during compilation,
#define MAINWINDOW_H

#include <QMainWindow>          // Includes the base class QMainWindow,

#include "student.h"                 //defines student class,search dialog
#include"searchstudentdialog.h"
#include<QTableWidget>                //used to display student data in table form
#include<QVector>                    //container, used to store Student objects

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow      // class MainWindow, which inherits from Qt’s QMainWindow.
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_btnAddStudent_clicked();
    void on_btnShowTable_clicked();
    void on_btndeleteStudent_clicked();
    void on_btnUpdateStudent_clicked();
    void on_btnsearchstudent_clicked();

    void on_btnlogout_clicked();

private:
    Ui::MainWindow *ui;            //Pointer to the UI class, which manages widgets
    QVector<Student>studentList;  //copy of vector container students

    void addStudentToTable(const Student &s);        //adds Student To File-->adds one student since paramter is given
    void saveStudentToFile(const Student &s);        //saves Student To File
    void updateStudentInCSV(const QString &originalRoll, const QString &name, //Updates existing data in file( roll number + all fields)
                            const QString &roll, const QString &branch,
                            const QString &gender, const QString &address);

    void saveTableToFile();        //Saves all students in table after app closes or updating/deleting etc


};
#endif // MAINWINDOW_H
