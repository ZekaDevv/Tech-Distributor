#include "invoice.h"
#include "ui_invoice.h"

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
