#include "loginwindow.h"      //custom class handles login dialog (inherits from QDialog).
#include "mainwindow.h"       //custom class for main application window (inherits from QMainWindow)
#include <QApplication>       // core application class required for all Qt GUI applications.

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);  //Initializes the Qt application.

    LoginWindow login;                      //Creates instance of login dialog.
    if(login.exec()==QDialog::Accepted){    //if login accepted
       MainWindow w;                         //create main window
        w.show();                           //show main window
        return a.exec();                    //Start Qt event loop to keep application running
    }
    return 0;                             //If login dialog was cancel/login failed, app exits immediately
}
