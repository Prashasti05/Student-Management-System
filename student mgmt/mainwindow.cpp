#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"addstudentdialog.h"                 
#include"student.h"
#include <QTextStream>
#include <QFile>
#include "studenttabledialog.h"                
#include<QMessageBox>
#include"upatestudentdialog.h"
#include<QTableWidgetItem>
#include"searchstudentdialog.h"
#include "loginwindow.h"



MainWindow::MainWindow(QWidget *parent)     //constructor
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);                       //Sets up all the UI elements (buttons, labels, etc.) 


    QPixmap addpic (":/img/pic/add-user_760792.png");      //load icon into qpixmap
    QPixmap showpic (":/img/pic/group_18476667.png");
    QPixmap searchpic (":/img/pic/search-user_11326123.png");
    QPixmap updatepic (":/img/pic/update2.png");
    QPixmap deletepic (":/img/pic/14314173.png");

    ui->label_add->setPixmap(addpic);         //Sets those icon into  labels
    ui->label_show->setPixmap(showpic);
    ui->label_search->setPixmap(searchpic);
    ui->label_update->setPixmap(updatepic);
    ui->label_delete->setPixmap(deletepic);

    ui->label_add->setScaledContents(true);   //Makes image fit exactly into label space.
    ui->label_show->setScaledContents(true);
    ui->label_search->setScaledContents(true);
    ui->label_update->setScaledContents(true);
    ui->label_delete->setScaledContents(true);

    connect(ui->btnupdatestudent, &QPushButton::clicked,this,&MainWindow::on_btnUpdateStudent_clicked);



    QFile file("students.csv");                              
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {  

        QTextStream in(&file);                              
        while (!in.atEnd()) {                               
            QString line = in.readLine();                    
            QStringList fields = line.split(",");            
            if (fields.size() == 5) {                        
                Student s;                                   
                s.name = fields[0];
                s.rollNo = fields[1];                 
                s.branch = fields[2];
                s.gender = fields[3];
                s.address = fields[4];
                addStudentToTable(s);                        // Show in table
                studentList.append(s);                       
            }
        }
        file.close();
    }


    // ------------------ Setup table UI ------------------
    ui->tableStudents->setColumnCount(5);                   // Set the no of col,header of col
    ui->tableStudents->setHorizontalHeaderLabels({"Name","Roll No","Branch","Gender","Address"});

     ui->tableStudents->setSortingEnabled(true);    // Enable sorting of table when clicking on headers

}

MainWindow::~MainWindow()
{
    delete ui;
}



  //add studentinfo to table widget
void MainWindow::addStudentToTable(const Student &s) {
    int row = ui->tableStudents->rowCount();                    
    ui->tableStudents->insertRow(row);                          

    ui->tableStudents->setItem(row, 0, new QTableWidgetItem(s.name));  
    ui->tableStudents->setItem(row, 1, new QTableWidgetItem(s.rollNo));
    ui->tableStudents->setItem(row, 2, new QTableWidgetItem(s.branch));
    ui->tableStudents->setItem(row, 3, new QTableWidgetItem(s.gender));
    ui->tableStudents->setItem(row, 4, new QTableWidgetItem(s.address));
}


//used when adding/append 1 new student entry
void MainWindow::saveStudentToFile(const Student &s){
    QFile file("students.csv");                              
    if(file.open(QIODevice::Append | QIODevice::Text)){      
        QTextStream out(&file);                      
        out<<s.name <<"," <<s.rollNo <<"," <<s.branch <<"," <<s.gender <<"," <<s.address<<"\n";
        file.close();
    }
}

//used when modifying/deleting already entered entries
void MainWindow::saveTableToFile()
{
    QFile file("students.csv");                                   
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {      
        QTextStream out(&file);                                   
        for (int row = 0; row < ui->tableStudents->rowCount(); ++row) {     
            QStringList rowData;                                           
            for (int col = 0; col < ui->tableStudents->columnCount(); ++col) { 
                rowData << ui->tableStudents->item(row, col)->text();       
            }
            out << rowData.join(",") << "\n";                       
        }
        file.close();
    }
}

void MainWindow::updateStudentInCSV(const QString &originalRoll, const QString &name,
                                    const QString &roll, const QString &branch,
                                    const QString &gender, const QString &address) {
    QFile file("students.csv");
    QList<QStringList> students;

    // Read existing student data from file nd load  into list students
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();             
            QStringList fields = line.split(",");
            students.append(fields);                 
        }
        file.close();
    }

    // Find and update the matching student by originalRoll
    for (QStringList &student : students) {
        if (student.size() >= 2 && student[1] == originalRoll) {   
            student[0] = name;
            student[1] = roll;                 
            student[2] = branch;
            student[3] = gender;
            student[4] = address;
            break;                               
        }
    }

    //Save the updated list back into the file
    if (file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        QTextStream out(&file);                 
        for (const QStringList &student : students) {
            out << student.join(",") << "\n";        
        }
        file.close();
    }
}






//---------------------------add Student button clicked---------------------------
void MainWindow::on_btnAddStudent_clicked()
{
    AddStudentDialog dialog;                        
    if(dialog.exec()==QDialog::Accepted){          
        Student s= dialog.getStudent();              
        addStudentToTable(s);
        saveStudentToFile(s);
        studentList.append(s);             
    }
}
//--------------------------------show student button clicked-----------------------------------
void MainWindow::on_btnShowTable_clicked()
{
    StudentTableDialog dialog(studentList,this);        
    dialog.exec();
}

//--------------------------------delete student button clicked-----------------------------------
void MainWindow::on_btndeleteStudent_clicked()
{
    int row=ui->tableStudents->currentRow();               
    if(row >=0){                                           
        ui->tableStudents->removeRow(row);                 
        saveTableToFile();                                 

    if(row<studentList.size()){                            
        studentList.removeAt(row);
    }

    QFile file("students.csv");              
    if(file.open(QIODevice::WriteOnly| QIODevice::Text)){
        QTextStream out(&file);
        for(const Student &s :studentList){
        out<<s.name<<","<<s.rollNo<<","<<s.branch<<","<<s.gender<<","<<s.address<<"\n";
        }
        file.close();
    }
    }else{
        QMessageBox::warning(this,"No Selection","Please select a student to delete");
    }

}


//----------------------update student button clicked-----------------------------------
void MainWindow::on_btnUpdateStudent_clicked()
{
    int currentRow = ui->tableStudents->currentRow();                         // Get selected row
    if (currentRow < 0) {                                                     //if not gives error box
        QMessageBox::warning(this, "No selection", "Please select a student to update.");
        return;
    }
    // Get existing student data from the selected row
    QString name = ui->tableStudents->item(currentRow, 0)->text();
    QString roll = ui->tableStudents->item(currentRow, 1)->text();
    QString branch = ui->tableStudents->item(currentRow, 2)->text();
    QString gender = ui->tableStudents->item(currentRow, 3)->text();
    QString address = ui->tableStudents->item(currentRow, 4)->text();

    QString originalRoll = roll;                       // Check to find the correct record in file


   UpateStudentDialog dialog(this);                     
    dialog.setStudentData(name, roll, branch, gender, address);   

    if (dialog.exec() == QDialog::Accepted) {       
        QString updatedName, updatedRoll, updatedBranch, updatedGender, updatedAddress;
        //get updated data entered by user from dialog.
        dialog.getStudentData(updatedName, updatedRoll, updatedBranch, updatedGender, updatedAddress);

        // Update UI table with new data
        ui->tableStudents->item(currentRow, 0)->setText(updatedName);
        ui->tableStudents->item(currentRow, 1)->setText(updatedRoll);
        ui->tableStudents->item(currentRow, 2)->setText(updatedBranch);
        ui->tableStudents->item(currentRow, 3)->setText(updatedGender);
        ui->tableStudents->item(currentRow, 4)->setText(updatedAddress);

        // Update file
        updateStudentInCSV(originalRoll, updatedName, updatedRoll, updatedBranch, updatedGender, updatedAddress);
        saveTableToFile();

    }
}

//---------------------search student button clicked-----------------------------------

void MainWindow::on_btnsearchstudent_clicked()
{
    studentList.clear();
    for (int row = 0; row < ui->tableStudents->rowCount(); ++row) {
        Student s;
        s.name = ui->tableStudents->item(row, 0)->text();
        s.rollNo = ui->tableStudents->item(row, 1)->text();
        s.branch = ui->tableStudents->item(row, 2)->text();
        s.gender = ui->tableStudents->item(row, 3)->text();
        s.address = ui->tableStudents->item(row, 4)->text();
        studentList.append(s);
    }
    searchstudentDialog dialog(studentList,this);  
    dialog.exec();

}

//---------------------------logout ------------------------------
void MainWindow::on_btnlogout_clicked()
{
    this->close();                                 

    LoginWindow *login =new LoginWindow();        
    login->exec();                                 
}


