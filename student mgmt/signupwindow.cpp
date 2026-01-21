#include "signupwindow.h"
#include "ui_signupwindow.h"
#include "loginwindow.h"

#include<QFile>                                
#include<QTextStream>                          
#include<QMessageBox>

signupwindow::signupwindow(QWidget *parent)
    : QDialog(parent)                             //calls qdialog constructor and new ui
    , ui(new Ui::signupwindow)
{
    ui->setupUi(this);

    //connect(ui->pushButton_register, &QPushButton::clicked, this, &signupwindow::on_pushButton_register_clicked);

}

signupwindow::~signupwindow()
{
    delete ui;                                        
}

void signupwindow::on_pushButton_register_clicked()
{
    QString username =ui->lineEdit_newusername->text().trimmed();               
    QString password =ui->lineEdit_newpassword->text().trimmed();               
    QString confirmpassword =ui->lineEdit_confirmpassword->text().trimmed();    

    if(username.isEmpty() || password.isEmpty() ||confirmpassword.isEmpty()){            //check if empty fields
        QMessageBox::warning(this,"Input Error","Please fill in all fields.");
        return;
    }
    if(password !=confirmpassword){                                                   //check if password do not match
        QMessageBox::warning(this,"Password Mismatch","Passwords do not match.");
        return;
    }

                                  //Else Open users.txt file to append the new user
    QFile file("users.txt");
    if(file.open(QIODevice::Append | QIODevice::Text)){         
        QTextStream out(&file);                               
        out<<username << ":"<<password<<"\n";                    
        file.close();

        QMessageBox::information(this,"Registration","User Registered Successfully.");
        this->accept();
    }
    else{
        QMessageBox::critical(this,"Error","Unable to Register.");

    }

}


void signupwindow::on_pushButton_signin_clicked()
{
    LoginWindow *login= new LoginWindow();      // Create a new login window
    login->show();                              
    this->close();                              
}



