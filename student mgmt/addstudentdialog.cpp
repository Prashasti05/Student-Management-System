#include "addstudentdialog.h"             //includes header file for this class.
#include "ui_addstudentdialog.h"          //Includes the UI class generated from the .ui file
#include <QMessageBox>


AddStudentDialog::AddStudentDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddStudentDialog)
{
    ui->setupUi(this);
}

AddStudentDialog::~AddStudentDialog()
{
    delete ui;
}
Student AddStudentDialog::getStudent() const {   //Student means func will return complete Student object.
    Student s;                              // Create a local Student object 's'.
    s.name=ui->namelineEdit->text();        // gets name from the text input field.
    s.rollNo=ui->rolllineEdit->text();
    s.branch=ui->branchlineEdit->text();
    s.gender=ui->gendercomboBox->currentText();
    s.address=ui->addresslineEdit->text();
    return s;                                   //Returns fully filled Student object.

}

void AddStudentDialog::on_btnSaveStudent_clicked()
{
    if(ui->namelineEdit->text().isEmpty()){             // Check if name field is empty.

        QMessageBox::warning(this,"Input Error","Name cannot be empty.");
        return;
    }
    accept();                     //accept - closes the dialog and indicate success.
}

