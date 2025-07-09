#ifndef SIGNUPWINDOW_H
#define SIGNUPWINDOW_H

#include <QWidget>      //Base class for all UI objects in Qt
#include <QDialog>     //widget used to create dialog window

namespace Ui {
class signupwindow;
}

class signupwindow : public QDialog   //class signupwindow is custom dialog,Inherits from QDialog
{
    Q_OBJECT     // Macro needed by all Qt classes that use signals/slots

public:
    explicit signupwindow(QWidget *parent = nullptr);
    ~signupwindow();

/*signals:
    void userRegistered(const QString &username, const QString &password);     // Signal emitted when new user is registered nd Passes username and password to whoever connected to this signal
*/

private slots:
    void on_pushButton_register_clicked();
    void on_pushButton_signin_clicked();

private:
    Ui::signupwindow *ui;  // Pointer to the UI class generated from the .ui file
};

#endif // SIGNUPWINDOW_H
