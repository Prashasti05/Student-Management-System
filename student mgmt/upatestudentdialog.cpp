#include "upatestudentdialog.h"
#include "ui_upatestudentdialog.h"

#include<QDialog>
#include"student.h"

UpateStudentDialog::UpateStudentDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::UpateStudentDialog)
{
    ui->setupUi(this);
    connect(ui->btnUpdateStudent, &QPushButton::clicked, this, &QDialog::accept);
    connect(ui->btnCancel, &QPushButton::clicked, this, &QDialog::reject);
}

UpateStudentDialog::~UpateStudentDialog()
{
    delete ui;
}
    //-------------INPUT----------
void UpateStudentDialog::setStudentData(const QString &name, const QString &rollNo, const QString &branch, const QString &gender, const QString &address)
{
    ui->namelineEdit->setText(name);
    ui->rolllineEdit->setText(rollNo);
    ui->branchlineEdit->setText(branch);
    ui->gendercomboBox->setCurrentText(gender);
    ui->addresslineEdit->setText(address);
}

     //----------oUTPUT-------------
void UpateStudentDialog::getStudentData(QString &name, QString &rollNo, QString &branch, QString &gender, QString &address) const
{
    name = ui->namelineEdit->text();
    rollNo = ui->rolllineEdit->text();
    branch = ui->branchlineEdit->text();
    gender = ui->gendercomboBox->currentText();
    address = ui->addresslineEdit->text();

}


