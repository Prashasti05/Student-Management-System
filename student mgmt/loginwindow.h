#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QDialog>      
#include <QMap>

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QDialog     
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();

private slots:
    void on_pushButton_login_clicked();
    void on_pushButton_register_clicked();
    void on_checkBox_showPassword_toggled(bool checked);


private:
    Ui::LoginWindow *ui;    

    QMap<QString,QString> users;    //qmap container to store username,password

    void loadUsers();
    void saveLastUser(const QString &username);  //helper func to store recent user
};

#endif // LOGINWINDOW_H
