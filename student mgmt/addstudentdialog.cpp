#include "addstudentdialog.h"             
#include "ui_addstudentdialog.h"          
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
Student AddStudentDialog::getStudent() const {   
    Student s;                              // Create a local Student object 's'.
    s.name=ui->namelineEdit->text();        // gets name from the text input field.
    s.rollNo=ui->rolllineEdit->text();
    s.branch=ui->branchlineEdit->text();
    s.gender=ui->gendercomboBox->currentText();
    s.address=ui->addresslineEdit->text();
    return s;                                  

}

void AddStudentDialog::on_btnSaveStudent_clicked()
{
    if(ui->namelineEdit->text().isEmpty()){          

        QMessageBox::warning(this,"Input Error","Name cannot be empty.");
        return;
    }
    accept();                    
}

