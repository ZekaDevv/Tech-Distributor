#include "invoice.h"
#include "ui_invoice.h"
#include "modalmsh.h"

invoice::invoice(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::invoice)
{
    ui->setupUi(this);
}

invoice::~invoice()
{
    delete ui;
}

void invoice::on_goBack_clicked() {
    this->close();
}


void invoice::on_buyConfirmation_clicked() {






    modalMsh windowModalMsh("Compra Realizada!");
    windowModalMsh.setModal(true);
    windowModalMsh.exec();
    this->close();
}

