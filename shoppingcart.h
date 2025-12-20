#ifndef SHOPPINGCART_H
#define SHOPPINGCART_H

#include <QDialog>
#include <QVector>

namespace Ui {
class shoppingCart;
}

class shoppingCart : public QDialog
{
    Q_OBJECT

public:
    explicit shoppingCart(
        QMap  <QString, int> productsCant, QWidget *parent = nullptr);
    ~shoppingCart();

private slots:
    void on_filterInput_textChanged(const QString &arg1);
    void on_orderDown_clicked();

    void on_orderUp_clicked();

    void on_resetTable_clicked();

    void on_buttonBack_clicked();

private:
    Ui::shoppingCart *ui;

    QMap  <QString, int> productsCantt;
    QMap <QString, int> productsPrice;
    struct productInfo {
        QString name;
        int price;
        int cant;
        int priceTotal;
    };

    QVector <productInfo> products;
    QVector <productInfo> productsSortD;
    QVector <productInfo> productsSortA;

    QVector <productInfo> selectionSort (const QVector <productInfo> &products, bool orde);
    void insertionTable (const QVector <productInfo> &items);
};

#endif // SHOPPINGCART_H
