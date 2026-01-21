#ifndef STUDENTTABLEDIALOG_H    
#define STUDENTTABLEDIALOG_H   

#include <QDialog>
#include"student.h"    

#include<QVector>    //Include QVector container class to handle a list of students

namespace Ui {
class StudentTableDialog;
}

class StudentTableDialog : public QDialog          
{
    Q_OBJECT

public:
    explicit StudentTableDialog(const QVector<Student> &students, QWidget *parent = nullptr);
    ~StudentTableDialog();


    void showEvent(QShowEvent *event) override;

private:
    Ui::StudentTableDialog *ui;
    void loadDataFromFile();              // Private helper func to load student data from a file
};

#endif // STUDENTTABLEDIALOG_H
