#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "products.h"
#include "newuser.h"
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QFile>
#include <QDir>
#include <QStandardPaths>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    ui->input_psw->setEchoMode(QLineEdit::Password);

    laodUser();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::laodUser() {
    QString path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir dir(path);
    if (!dir.exists()) dir.mkpath(".");
    path = path + "/usuarios_app.json";

    QFile file(path);

    if(file.open(QIODevice::ReadOnly)) {
        QByteArray data = file.readAll();
        QJsonDocument doc = QJsonDocument::fromJson(data);
        arrUsers = doc.array();
        file.close();
    } else {
        arrUsers = QJsonArray();
    }
}



void MainWindow::on_bottonIng_clicked() {
    QString user = ui->input_user->text().toLower(),
        psw = ui->input_psw->text(),
        keyUser = "user",
        keyPsw = "password";
    bool isValidUser = false;

    for (const auto &item : arrUsers) {
        QJsonObject obj = item.toObject();

        if(obj[keyUser].toString() == user) {
            isValidUser = true;

            if(obj[keyPsw].toString() == psw) {
                this->hide();

                Products ventana;

                ventana.setModal(true);
                ventana.exec();

                this->show();

                ui->input_user->clear();
                ui->input_psw->clear();
                return;

            } else {

                ui->label_error->setText("Contraseña incorrecta");
                return;
            }
        }
    }

    if(!isValidUser) {
        ui->label_error->setText("Usuario no encontrado");
    }
}

void MainWindow::on_newUser_clicked() {
    newUser WindowNewUser;

    this->hide();

    WindowNewUser.setModal(true);
    WindowNewUser.exec();

    laodUser();

    this->show();
}

void MainWindow::on_joinAdmin_clicked() {

}


/*
Cosas por terminal

    - Construir logica del Admin (elimiar usuarios, cambiar preios y cantidad de proucto)
    - definr json que maneje los productos (name, price, cant)
    - Actualizar products (cantidad de productos) y validar que no pueda comprar mas del stock
    y restar stok
    - Terminar facturacion (logica de pasar datos para la misma)
    - Y por fin termine hijueputa

*/

