#ifndef STUDENTTABLEDIALOG_H    //ifndef
#define STUDENTTABLEDIALOG_H   //define header file

#include <QDialog>
#include"student.h"    // Include the Student class definition

#include<QVector>    //Include QVector container class to handle a list of students

namespace Ui {
class StudentTableDialog;
}

class StudentTableDialog : public QDialog          // Declare StudentTableDialog class, inherited from QDialog
{
    Q_OBJECT

public:
    explicit StudentTableDialog(const QVector<Student> &students, QWidget *parent = nullptr);
    ~StudentTableDialog();

    /*When you show a dialog using .show() or .exec(), Qt automatically calls showEvent() at last moment/just before the window appears.
     By overriding this function, you can run your own code (like loading/refreshing data) right before the dialog is shown.*/

    void showEvent(QShowEvent *event) override;
    // Overrides the showEvent() method to perform actions when the dialog is shown (e.g., load data)

private:
    Ui::StudentTableDialog *ui;
    void loadDataFromFile();              // Private helper func to load student data from a file
};

#endif // STUDENTTABLEDIALOG_H
