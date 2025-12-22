#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "admin.h"
#include "products.h"
#include "newuser.h"
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QFile>
#include <QDir>
#include <QStandardPaths>
#include <QDebug>

static const QString KEY_USER = "user";
static const QString KEY_PASS = "password";

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    ui->input_psw->setEchoMode(QLineEdit::Password);

    isAdmin = false;

    loadData(arrUsers, "usuarios_app.json");

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadData(QJsonArray &arr, const QString &fileName) {
    QString path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir dir(path);
    if (!dir.exists()) dir.mkpath(".");
    path = dir.filePath(fileName);

    QFile file(path);

    if(file.open(QIODevice::ReadOnly)) {
        QByteArray data = file.readAll();
        QJsonDocument doc = QJsonDocument::fromJson(data);
        arr = doc.array();
        file.close();
    } else {
        arr = QJsonArray();
    }
}

void MainWindow::createDefaultAdmin() {
    QJsonObject defaultAdmin;
    defaultAdmin[KEY_USER] = "admin";
    defaultAdmin[KEY_PASS] = "1234";


    arrUsersAdmins.append(defaultAdmin);

    QString path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir dir(path);
    if (!dir.exists()) dir.mkpath(".");
    path = dir.filePath("admin_app.json");

    QFile file(path);
    if (file.open(QIODevice::WriteOnly)) {
        QJsonDocument doc(arrUsersAdmins);
        file.write(doc.toJson());
        file.close();
    }
}

bool MainWindow::logIn(const QJsonArray &arr) {
    QString user = ui->input_user->text().trimmed().toLower(),
        psw = ui->input_psw->text().trimmed();
    bool isValidUser = false;


    if (user.isEmpty() || psw.isEmpty()) {
        ui->label_error->setText("Llene todos los campos");
        return isValidUser;
    }


    for (const auto &item : arr) {
        QJsonObject obj = item.toObject();

        if(obj[KEY_USER].toString() == user) {
            isValidUser = true;

            if(obj[KEY_PASS].toString() == psw) {

                ui->input_user->clear();
                ui->input_psw->clear();
                return isValidUser;

            } else {
                isValidUser = false;

                ui->label_error->setText("Contraseña incorrecta");
                return isValidUser;
            }
        }
    }

    if(!isValidUser) {
        ui->label_error->setText("Usuario no encontrado");
        return isValidUser;
    }

    return isValidUser;
}


void MainWindow::on_bottonIng_clicked() {
    ui->label_error->clear();

    if(isAdmin) {
        if(logIn(arrUsersAdmins)){
            admin wnidowAdmin;

            this->hide();

            wnidowAdmin.setModal(true);
            wnidowAdmin.exec();

            this->show();
        }
    }else{
        if(logIn(arrUsers)){
            Products windowProducts;

            this->hide();

            windowProducts.setModal(true);
            windowProducts.exec();

            this->show();
        }
    }
}

void MainWindow::on_newUser_clicked() {
    newUser WindowNewUser;

    this->hide();

    WindowNewUser.setModal(true);
    WindowNewUser.exec();

    loadData(arrUsers, "usuarios_app.json");

    this->show();
}

void MainWindow::on_joinAdmin_clicked() {
    isAdmin = !isAdmin;

    if(isAdmin) {
        loadData(arrUsersAdmins, "admin_app.json");
        ui->label_user->setText("Usuario Admin");
        ui->newUser->setEnabled(false);
        ui->joinAdmin->setText("Ingresar como Usuario");
    }else {
        ui->label_user->setText("Usuario");
        ui->newUser->setEnabled(true);
        ui->joinAdmin->setText("Ingrear como Administrador");
    }
}


/*
Cosas por terminal

    - Terminar logica de los usuarios en admin
    - Actualizar products (cantidad de productos) y validar que no pueda comprar mas del stock
    y restar stock en products
    - cambiar el array que consume la tabla por el json
    - Terminar facturacion (logica de pasar datos para la misma)
    - Y por fin termine hijueputa
*/

