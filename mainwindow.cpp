#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "products.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_bottonIng_clicked()
{
    std::string userBase = "zeka";
    QString user;
    int pswBase = 49137520,
        psw;


    user = ui->input_user->text().toLower();
    psw = ui->input_psw->text().toFloat();

    if (user == userBase && psw == pswBase) {
        ui->label_error->clear();

        this->hide();

        Products ventana;
        ventana.setModal(true);
        ventana.exec();
        this->show();
        ui->input_user->clear();
        ui->input_psw->clear();

    } else {
        ui->label_error->setText("Error: datos incorrectos, vuelve a intentarlo");
        ui->input_user->clear();
        ui->input_psw->clear();


    }

}

