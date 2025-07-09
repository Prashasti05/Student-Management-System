#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"addstudentdialog.h"                 // Dialog to add a student
#include"student.h"
#include <QTextStream>
#include <QFile>
#include "studenttabledialog.h"                 // Dialog to show student
#include<QMessageBox>
#include"upatestudentdialog.h"
#include<QTableWidgetItem>
#include"searchstudentdialog.h"
#include "loginwindow.h"



MainWindow::MainWindow(QWidget *parent)     //constructor
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);                       //Sets up all the UI elements (buttons, labels, etc.) f


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



    QFile file("students.csv");                              // Create a QFile obj
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {  // Try to open the file in read-only mode

        QTextStream in(&file);                               // Create QTextStream to read from file
        while (!in.atEnd()) {                                // Loop through the file
            QString line = in.readLine();                    // Read one line from the file
            QStringList fields = line.split(",");            // Split the line using comma as delimiter
            if (fields.size() == 5) {                        // Check if line has exactly 5 fields
                Student s;                                   // Create a Student obj to store data
                s.name = fields[0];
                s.rollNo = fields[1];                 // Assign values from CSV fields to Student obj
                s.branch = fields[2];
                s.gender = fields[3];
                s.address = fields[4];
                addStudentToTable(s);                        // Show in table
                studentList.append(s);                       //also add student to internal list
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
    int row = ui->tableStudents->rowCount();                    // Get curr number of rows
    ui->tableStudents->insertRow(row);                          // Insert a new empty row at tht posn

    ui->tableStudents->setItem(row, 0, new QTableWidgetItem(s.name));  // Set each col's cell value in new row with student data
    ui->tableStudents->setItem(row, 1, new QTableWidgetItem(s.rollNo));
    ui->tableStudents->setItem(row, 2, new QTableWidgetItem(s.branch));
    ui->tableStudents->setItem(row, 3, new QTableWidgetItem(s.gender));
    ui->tableStudents->setItem(row, 4, new QTableWidgetItem(s.address));
}


//used when adding/append 1 new student entry
void MainWindow::saveStudentToFile(const Student &s){
    QFile file("students.csv");                               //open csv file
    if(file.open(QIODevice::Append | QIODevice::Text)){      // Open in append mode
        QTextStream out(&file);                      // Create stream to write text seprated with commas
        out<<s.name <<"," <<s.rollNo <<"," <<s.branch <<"," <<s.gender <<"," <<s.address<<"\n";
        file.close();
    }
}

//used when modifying/deleting already entered entries
void MainWindow::saveTableToFile()
{
    QFile file("students.csv");                                   //QFile obj is created that points to file
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {      // file is open in WriteOnly mode,ie Existing contnt will be overwritten
        QTextStream out(&file);                                   // Stream to write
        for (int row = 0; row < ui->tableStudents->rowCount(); ++row) {     // a loop to go through each row
            QStringList rowData;                                            //temp list to hold column values of one row.
            for (int col = 0; col < ui->tableStudents->columnCount(); ++col) { //Nested loop iterates over each col in curr row
                rowData << ui->tableStudents->item(row, col)->text();       //For curr cell at pos(row,col),it extracts txt content nd appends it to rowData.
            }
            out << rowData.join(",") << "\n";                         //converts list into a comma-separated string.
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
            QString line = in.readLine();             // Read each line (one student)
            QStringList fields = line.split(",");
            students.append(fields);                  // Store fields (columns) in list
        }
        file.close();
    }

    // Find and update the matching student by originalRoll
    for (QStringList &student : students) {
        if (student.size() >= 2 && student[1] == originalRoll) {   //check if list exist, student[1] is Roll No ==orig roll
            student[0] = name;
            student[1] = roll;                 //update all fields
            student[2] = branch;
            student[3] = gender;
            student[4] = address;
            break;                               //Exit loop after updating
        }
    }

    //Save the updated list back into the file
    if (file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        QTextStream out(&file);                  //file opened in write mode with truncate which erases old content
        for (const QStringList &student : students) {
            out << student.join(",") << "\n";        // Convert list back to CSV line
        }
        file.close();
    }
}






//---------------------------add Student button clicked---------------------------
void MainWindow::on_btnAddStudent_clicked()
{
    AddStudentDialog dialog;                        // Create add-student dialog win
    if(dialog.exec()==QDialog::Accepted){           // Show dialog and check if user clicked OK
        Student s= dialog.getStudent();              // getter func Gets student info entered by user
        addStudentToTable(s);
        saveStudentToFile(s);
        studentList.append(s);              // add student to table,file,internal list
    }
}
//--------------------------------show student button clicked-----------------------------------
void MainWindow::on_btnShowTable_clicked()
{
    StudentTableDialog dialog(studentList,this);        // Create dialog and pass student list
    dialog.exec();
}

//--------------------------------delete student button clicked-----------------------------------
void MainWindow::on_btndeleteStudent_clicked()
{
    int row=ui->tableStudents->currentRow();               // Get selected row
    if(row >=0){                                           // Make sure a row is selected
        ui->tableStudents->removeRow(row);                 // Remove from table
        saveTableToFile();                                 // Save updated table to file

    if(row<studentList.size()){                            // Also remove from internal list
        studentList.removeAt(row);
    }

    QFile file("students.csv");              // Rewrite file with updated student list
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


//--------------------------------update student button clicked-----------------------------------
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


   UpateStudentDialog dialog(this);                     //open update dialog
    dialog.setStudentData(name, roll, branch, gender, address);   // and Pre-fills input field with curr data

    if (dialog.exec() == QDialog::Accepted) {       //Shows the dialog,If user clicks OK, proceed to upd data.
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

       // studentList.append(s);
    }
}



//--------------------------------search student button clicked-----------------------------------

void MainWindow::on_btnsearchstudent_clicked()
{
    searchstudentDialog dialog(studentList,this);  // Open search dialog with student list
    dialog.exec();

}

//---------------------------logout button clicked-------------------------------
void MainWindow::on_btnlogout_clicked()
{
    this->close();                                 // Close main window

    LoginWindow *login =new LoginWindow();         // Create login window
    login->exec();                                 // Show login window
}

