#ifndef SIGNUPWINDOW_H
#define SIGNUPWINDOW_H

#include <QWidget>      
#include <QDialog>     

namespace Ui {
class signupwindow;
}

class signupwindow : public QDialog   
{
    Q_OBJECT     

public:
    explicit signupwindow(QWidget *parent = nullptr);
    ~signupwindow();

/*signals:
    void userRegistered(const QString &username, const QString &password);     
*/

private slots:
    void on_pushButton_register_clicked();
    void on_pushButton_signin_clicked();

private:
    Ui::signupwindow *ui;  
};

#endif // SIGNUPWINDOW_H

