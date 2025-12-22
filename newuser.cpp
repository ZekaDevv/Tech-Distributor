#include "newuser.h"
#include "ui_newuser.h"
#include "modalmsh.h"
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QFile>
#include <QStandardPaths>
#include <QDir>

static const QString RX_EMAIL = R"(^[\w.-]+@([\w-]+\.)+[\w-]{2,4}$)";
static const QString RX_NAME  = R"(^[A-Za-zÁ-ÿ\s]{3,30}$)";
static const QString RX_USER  = R"(^[A-Za-z0-9]{3,20}$)";
static const QString RX_PASS  = R"(^[0-9]{4,15}$)";
static const QString RX_ID  = R"(^[0-9]{1,8}$)";

newUser::newUser(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::newUser)
{
    ui->setupUi(this);

    ui->input_psw->setEchoMode(QLineEdit::Password);
    ui->input_pswC->setEchoMode(QLineEdit::Password);

    loadUser();
}

newUser::~newUser()
{
    delete ui;
}

void newUser::on_goBack_clicked() {
    this->close();
}



void newUser::loadUser() {
    QString path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir dir(path);
    if (!dir.exists()) dir.mkpath(".");
    filePath = path + "/usuarios_app.json";

    QFile file(filePath);
    if(file.open(QIODevice::ReadOnly)) {
        QByteArray data = file.readAll();
        QJsonDocument doc = QJsonDocument::fromJson(data);
        arrUsers = doc.array();
        file.close();
    }
};



void newUser::saveUser() {
    QJsonObject newUserObj;
    newUserObj["names"] = ui->input_name->text();
    newUserObj["lastNames"] = ui->input_lastName->text();
    newUserObj["user"] = ui->input_user->text().toLower();
    newUserObj["email"] = ui->input_email->text();
    newUserObj["password"] = ui->input_psw->text();;
    newUserObj["ID"] = ui->input_id->text();;

    QFile file(filePath);

    arrUsers.append(newUserObj);

    if (file.open(QIODevice::WriteOnly)) {
        QJsonDocument doc(arrUsers);
        file.write(doc.toJson());
        file.close();
    }
}




bool newUser::validateField (QLineEdit *input, QLabel *errorLabel,  const QString &pattern, const QString &errorMsg) {

    QRegularExpression rgx(pattern);

    if (!rgx.match(input->text()).hasMatch()) {
        errorLabel->setText(errorMsg);
        return false;
    }

    errorLabel->clear();
    return true;
}



bool newUser::isDuplicate (const QString &value, const QString &key) {

    for (int i = 0; i < arrUsers.size(); i++) {
        const auto &item = arrUsers[i];
        if(item.toObject()[key].toString() == value) {
            return true;
        }
    }

    return false;
}



bool newUser::validateForm (const QJsonArray arrUsers) {
    bool isValid = true;

    isValid &= validateField(ui->input_name, ui->label_error_name, RX_NAME, "Nombres invalidos");
    isValid &= validateField(ui->input_lastName, ui->label_error_lastName, RX_NAME, "Apellidos invalidos");
    isValid &= validateField(ui->input_id, ui->label_error_id, RX_ID, "Cedula no valida");


    if(validateField(ui->input_user, ui->label_error_user, RX_USER, "Usuario invalido")) {

        if(isDuplicate(ui->input_user->text(), "user")) {
            ui->label_error_user->setText("Usuario ya existente");
            isValid = false;
        }

    }else {
        isValid = false;
    }


    if(validateField(ui->input_email, ui->label_error_email, RX_EMAIL, "Email no valiido")) {

        if(isDuplicate(ui->input_email->text(), "email")) {
            ui->label_error_email->setText("Email ya utilizado");
            isValid = false;
        }

    }else {
        isValid = false;
    }


    isValid &= validateField(ui->input_psw, ui->label_error_psw, RX_PASS, "Contraseña no valido");


    if(ui->input_pswC->text() != ui->input_psw->text()) {
        ui->label_error_pswC->setText("No coinciden la contraseña");
        isValid = false;
    }else {
        ui->input_pswC->clear();
    }


    return isValid;
}



void newUser::on_registerUser_clicked() {

    if(!validateForm(arrUsers)) return;
    saveUser();

    modalMsh windowModalMsh("Usuario Creado!");
    windowModalMsh.setModal(true);
    windowModalMsh.exec();

    this->close();
}
