#include "modalmsh.h"
#include "ui_modalmsh.h"

modalMsh::modalMsh(const QString &title, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::modalMsh)
{
    ui->setupUi(this);

    ui->msg->setText(title);
}

modalMsh::~modalMsh()
{
    delete ui;
}

void modalMsh::on_continueProgram_clicked()
{
    this->close();
}

