#include "searchstudentdialog.h"                 //Includes header file for this class
#include "ui_searchstudentdialog.h"              //Includes ato generated ui class from ui file
#include"mainwindow.h"                           //Includes header for MainWindow
#include<QMessageBox>
//#include<QTableWidget>                           //Imports QTableWidget, used for displaying data

searchstudentDialog::searchstudentDialog(const QVector<Student> &students, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::searchstudentDialog),   //Create new instance of UI class,Initialize member variable studentList with passed students
      studentList(students)             //create a local  editable copy of student -- studentList for searching/updating
{
    ui->setupUi(this);
   // connect(ui->btnSearch, &QPushButton::clicked,this, &QDialog::accept);

}

searchstudentDialog::~searchstudentDialog()
{
    delete ui;
}

void searchstudentDialog::on_btnSearch_clicked()
{
    QString keyword = ui->lineEdit_search->text().trimmed();                                  // Get text from search box and trim spaces

    if (keyword.isEmpty()) {                                                                  // Check if search box is empty
        QMessageBox::information(this, "Search", "Please enter a name or roll number.");
        return;
    }
    for (const Student &s : studentList) {                                                  // Loop through each student in the list
        if (s.name.contains(keyword, Qt::CaseInsensitive) || s.rollNo == keyword) {         // Check if name contains keyword (case-insensitive) || roll no matches

            // Create formatted string with student details
            QString result = "Name: " + s.name + "\nRoll No: " + s.rollNo +
                             "\nBranch: " + s.branch + "\nGender: " + s.gender +
                             "\nAddress: " + s.address;

            QMessageBox::information(this, "Student Found", result);                   // Show the student info in a popup
            return;
        }
    }

    QMessageBox::information(this, "Not Found", "No matching student found.");         // No match found
}




