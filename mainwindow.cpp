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

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    ui->input_psw->setEchoMode(QLineEdit::Password);

    /*QString path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir dir(path);
    if (!dir.exists()) dir.mkpath(".");
    path = path + "/usuarios_app.json";

    QFile file(path);

    if(file.open(QIODevice::ReadOnly)) {
        QByteArray data = file.readAll();
        QJsonDocument doc = QJsonDocument::fromJson(data);
        arrUsers = doc.array();
        file.close();
    }
*/
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_bottonIng_clicked()
{
    QString user, psw,
            keyUser = "user",
            keyPsw = "password";
    bool isValidUser = true;

    user = ui->input_user->text().toLower();
    psw = ui->input_psw->text();
    ui->label_error->clear();

    for (int i = 0; i < arrUsers.size(); i++) {
        const auto &item = arrUsers[i];

        if(item.toObject()[keyUser].toString() == user) {
            if(item.toObject()[keyPsw].toString() != psw) {
                ui->label_error->setText("Contraseña incorrecta");
                return;
            }
            isValidUser = true;
            break;
        }else {
            isValidUser = false;
        }
    }

    if(!isValidUser) {
        ui->label_error->setText("Usuario no encontrado");
        return;
    }

    this->hide();

    Products ventana;

    ventana.setModal(true);
    ventana.exec();

    this->show();

    ui->input_user->clear();
    ui->input_psw->clear();

}


void MainWindow::on_newUser_clicked() {
    newUser WindowNewUser;

    this->hide();

    WindowNewUser.setModal(true);
    WindowNewUser.exec();

    this->show();
}


void MainWindow::on_joinAdmin_clicked() {

}


/*
Cosas por terminal

    - hacer que el mainWindows pueda consumr el json y logear
    - Construir logica del Admin (elimiar usuarios, cambiar preios y cantidad de proucto)
    - definr json que maneje los productos (name, price, cant)
    - Actualizar products (cantidad de productos) y validar que no pueda comprar mas del stock
    y restar stok
    - Terminar facturacion (logica de pasar datos para la misma)
    - Y por fin termine hijueputa

*/

