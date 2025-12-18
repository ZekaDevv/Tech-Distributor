#ifndef SHOPPINGCART_H
#define SHOPPINGCART_H

#include <QWidget>

namespace Ui {
class shoppingCart;
}

class shoppingCart : public QWidget
{
    Q_OBJECT

public:
    explicit shoppingCart(QWidget *parent = nullptr);
    ~shoppingCart();

private:
    Ui::shoppingCart *ui;
};

#endif // SHOPPINGCART_H
