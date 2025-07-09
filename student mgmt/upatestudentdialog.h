#ifndef UPATESTUDENTDIALOG_H
#define UPATESTUDENTDIALOG_H

#include <QDialog>
#include "student.h"

namespace Ui {
class UpateStudentDialog;
}

class UpateStudentDialog : public QDialog
{
    Q_OBJECT

public:
    explicit UpateStudentDialog(QWidget *parent = nullptr);
    ~UpateStudentDialog();

    //these are setter and getter function to get student data
    void setStudentData(const QString &name, const QString &rollNo, const QString &branch, const QString &gender, const QString &address);
    void getStudentData(QString &name, QString &rollNo, QString &branch, QString &gender, QString &address) const;

private slots:
    void on_btnUpdateStudent_clicked();

private:
    Ui::UpateStudentDialog *ui;
};

#endif // UPATESTUDENTDIALOG_H
