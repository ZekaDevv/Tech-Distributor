#include "shoppingcart.h"
#include "ui_shoppingcart.h"

shoppingCart::shoppingCart(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::shoppingCart)
{
    ui->setupUi(this);
}

shoppingCart::~shoppingCart()
{
    delete ui;
}
