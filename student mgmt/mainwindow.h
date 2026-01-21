#ifndef MAINWINDOW_H        
#define MAINWINDOW_H

#include <QMainWindow>          

#include "student.h"                 
#include"searchstudentdialog.h"
#include<QTableWidget>                
#include<QVector>                   

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow      
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

    void addStudentToTable(const Student &s);        
    void saveStudentToFile(const Student &s);        
    void updateStudentInCSV(const QString &originalRoll, const QString &name, 
                            const QString &roll, const QString &branch,
                            const QString &gender, const QString &address);

    void saveTableToFile();        


};
#endif // MAINWINDOW_H

