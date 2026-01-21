#include "studenttabledialog.h"
#include "ui_studenttabledialog.h"
#include"student.h"                    
#include <QFile>

StudentTableDialog::StudentTableDialog(const QVector<Student> &students, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::StudentTableDialog)
{
    ui->setupUi(this);

    //---set up table widget--------
    ui->tableDialogWidget->setColumnCount(5);                               //set no of col and col headers
    ui->tableDialogWidget->setHorizontalHeaderLabels({"Name","Roll No","Branch","Gender","Address"});
    ui->tableDialogWidget->setRowCount(students.size());                     //set no of rows

    // --- fill the table with student data by looping through all students----
    for(int i=0;i<students.size();i++){

        ui->tableDialogWidget->setItem(i, 0, new QTableWidgetItem(students[i].name));
        ui->tableDialogWidget->setItem(i, 1, new QTableWidgetItem(students[i].rollNo));
        ui->tableDialogWidget->setItem(i, 2, new QTableWidgetItem(students[i].branch));
        ui->tableDialogWidget->setItem(i, 3, new QTableWidgetItem(students[i].gender));
        ui->tableDialogWidget->setItem(i, 4, new QTableWidgetItem(students[i].address));
    }
    ui->tableDialogWidget->setSortingEnabled(true);         // Allow sorting by clicking headers
}

// --- Function to load student data from a CSV file into the table ---
void StudentTableDialog::loadDataFromFile()
{
    QFile file("students.csv");                              //Creates a QFile obj
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {  //Opens file in read-only mode.
        QTextStream in(&file);                             
        ui->tableDialogWidget->setRowCount(0);              

        while (!in.atEnd()) {                                
            QString line = in.readLine();                    
            QStringList fields = line.split(",");            
            int row = ui->tableDialogWidget->rowCount();     
            ui->tableDialogWidget->insertRow(row);           

            for (int col = 0; col < fields.size(); ++col) {   
                ui->tableDialogWidget->setItem(row, col, new QTableWidgetItem(fields[col]));
            }
        }

        file.close();
    }
}
void StudentTableDialog::showEvent(QShowEvent *event)   
{
    QDialog::showEvent(event);                       
    loadDataFromFile();               
}


StudentTableDialog::~StudentTableDialog()
{
    delete ui;
}


