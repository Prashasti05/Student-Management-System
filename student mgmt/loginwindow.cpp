#include "loginwindow.h"
#include "ui_loginwindow.h"
#include"signupwindow.h"
#include "mainwindow.h"

#include <QMessageBox>
#include<QFile>             // For file operations like opening/saving text file
#include<QTextStream>       // For reading/writing user data to files

LoginWindow::LoginWindow(QWidget *parent)
    : QDialog(parent)            // Call QDialog constructor with parent
    , ui(new Ui::LoginWindow)     // Create the UI object

{
    ui->setupUi(this);
    loadUsers();               // Load existing users from file into `users` map


    //connect(ui->pushButton_login, &QPushButton::clicked, this, &MainWindow::on_pushButton_login_clicked);
    //  connect(ui->pushButton_register, &QPushButton::clicked, this,&MainWindow::on_pushButton_register_clicked);
    connect(ui->checkBox_showPassword, &QCheckBox::toggled, this,[=](bool checked){
        ui->lineEdit_password->setEchoMode(checked ? QLineEdit::Normal : QLineEdit::Password);  //show password
    });
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::loadUsers(){    //to load users from txt file to map
    users.clear();                        // Clear existing entries from map
    QFile file("users.txt");              // creates a qfile obj with filename= users.txt

    if(file.open(QIODevice::ReadOnly | QIODevice::Text)){ //opens file in read-only mode
        QTextStream in(&file);                          //Sets up text stream to read file line by line

        while(!in.atEnd()){               //untill loop reaches end of file
            QString line= in.readLine().trimmed();    //Reads single line from file nd removes any leading whitespace.
            QStringList parts= line.split(":");       //Splits line into parts using the colon : as a delimiter.
            if(parts.size()==2){                   //since it has 2parts-usernme nd password.Ensures line contains exactly 1colon
                QString username =parts[0].trimmed();   //Removes extra whitespace from both
                QString password =parts[1].trimmed();
                users[username] = password;   //nd Store them in the users map
            }
        }
        file.close();
    }
}

void LoginWindow::saveLastUser(const QString &username)      //saves last user
{
    QFile file("lastuser.txt");     // creates a QFile obj
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {  //try to Open file in write-only mode
        QTextStream out(&file);                              //QTextStream named out is created and linked to the file.
        out << username;                            //writes username in file
        file.close();
    }
}


void LoginWindow::on_pushButton_login_clicked()
{
    loadUsers();                                          // Reload users from file

    QString username =ui->lineEdit_username->text().trimmed();  //get username
    QString password=ui->lineEdit_password->text().trimmed();   //get password

    if(username.isEmpty() || password.isEmpty()){                         // Check if fields are empty
        QMessageBox::warning(this,"Login","Please fill in all fields.");
        return;
    }
    if(users.contains(username) && users[username]==password){             // check if Validate credentials
        saveLastUser(username);                                             // Save username for later
        QMessageBox::information(this,"Welcome","Welcome "+ username +" !");

        accept();                         //closes login win nd opens main win
    }
    else{
        QMessageBox::warning(this,"Login Failed","Invalid credentials.");
    }
}


void LoginWindow::on_pushButton_register_clicked()
{
    signupwindow *signup_win=new signupwindow(this);     // Create the sign-up window
    signup_win->exec();                                  // Opens it
    //this->close();
}

