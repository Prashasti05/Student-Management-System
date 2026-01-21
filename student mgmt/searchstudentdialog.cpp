#include "searchstudentdialog.h"                 
#include "ui_searchstudentdialog.h"              
#include"mainwindow.h"                          
#include<QMessageBox>
//#include<QTableWidget>                           

searchstudentDialog::searchstudentDialog(const QVector<Student> &students, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::searchstudentDialog),   
      studentList(students)             
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
    QString keyword = ui->lineEdit_search->text().trimmed();                                  

    if (keyword.isEmpty()) {                                                                 
        QMessageBox::information(this, "Search", "Please enter a name or roll number.");
        return;
    }
    for (const Student &s : studentList) {                                                  
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





