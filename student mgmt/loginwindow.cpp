#include "loginwindow.h"
#include "ui_loginwindow.h"
#include"signupwindow.h"
#include "mainwindow.h"

#include <QMessageBox>
#include<QFile>             
#include<QTextStream>       

LoginWindow::LoginWindow(QWidget *parent)
    : QDialog(parent)            
    , ui(new Ui::LoginWindow)    

{
    ui->setupUi(this);
    loadUsers();              

    connect(ui->checkBox_showPassword, &QCheckBox::toggled, this,[=](bool checked){
        ui->lineEdit_password->setEchoMode(checked ? QLineEdit::Normal : QLineEdit::Password);  //show password
    });
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::loadUsers(){    
    users.clear();                        
    QFile file("users.txt");             

    if(file.open(QIODevice::ReadOnly | QIODevice::Text)){ 
        QTextStream in(&file);                          

        while(!in.atEnd()){               
            QString line= in.readLine().trimmed();    
            QStringList parts= line.split(":");       
            if(parts.size()==2){                   
                QString username =parts[0].trimmed();   
                QString password =parts[1].trimmed();
                users[username] = password;        
            }
        }
        file.close();
    }
}

void LoginWindow::saveLastUser(const QString &username)      //saves last user
{
    QFile file("lastuser.txt");     
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {  
        QTextStream out(&file);                              
        out << username;                            
        file.close();
    }
}


void LoginWindow::on_pushButton_login_clicked()
{
    loadUsers();                                        

    QString username =ui->lineEdit_username->text().trimmed();  //get username
    QString password=ui->lineEdit_password->text().trimmed();   //get password

    if(username.isEmpty() || password.isEmpty()){                         
        QMessageBox::warning(this,"Login","Please fill in all fields.");
        return;
    }
    if(users.contains(username) && users[username]==password){             // check if Validate credentials
        saveLastUser(username);                                             // Save username for later
        QMessageBox::information(this,"Welcome","Welcome "+ username +" !");

        accept();                         
    }
    else{
        QMessageBox::warning(this,"Login Failed","Invalid credentials.");
    }
}


void LoginWindow::on_pushButton_register_clicked()
{
    signupwindow *signup_win=new signupwindow(this);     
    signup_win->exec();                                 
    //this->close();
}

