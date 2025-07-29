#include "loginwindow.h"      
#include "mainwindow.h"     
#include <QApplication>       

int main(int argc, char *argv[])
{
    QApplication a(argc, argv); 

    LoginWindow login;                     
    if(login.exec()==QDialog::Accepted){   
       MainWindow w;                         
        w.show();                           
        return a.exec();                    
    }
    return 0;                           
}
