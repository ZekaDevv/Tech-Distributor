#include "admin.h"
#include "ui_admin.h"
#include "modalmsh.h"

admin::admin(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::admin)
{
    ui->setupUi(this);
}

admin::~admin()
{
    delete ui;
}

void admin::on_returnP1_clicked()
{
    this->close();
}


void admin::on_addCart_clicked() {











    modalMsh windowModalMsh("Cambios realizados");
    windowModalMsh.setModal(true);
    windowModalMsh.exec();
}

