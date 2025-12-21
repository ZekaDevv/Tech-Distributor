#ifndef NEWUSER_H
#define NEWUSER_H

#include <QDialog>
#include <QJsonArray>
#include <QLineEdit>
#include <QLabel>

namespace Ui {
class newUser;
}

class newUser : public QDialog
{
    Q_OBJECT

public:
    explicit newUser(QWidget *parent = nullptr);
    ~newUser();

private slots:

    void on_goBack_clicked();

    void on_registerUser_clicked();

    bool validateForm(const QJsonArray arrUsers);
    bool validateField (QLineEdit *input, QLabel *errorLabel,  const QString &pattern, const QString &errorMsg);

private:
    Ui::newUser *ui;

    struct user {
        QString names,
                lastNames,
                user,
                email,
                password;
    } tempUser;

    QJsonArray arrUsers;
    QString filePath;

    void loadUser();
    void saveUser();

    bool isDuplicate(const QString &value, const QString &key);


};

#endif // NEWUSER_H
