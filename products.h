#ifndef PRODUCTS_H
#define PRODUCTS_H

#include <QDialog>

#include <QVector>
#include <QSpinBox>
#include <QLabel>

namespace Ui {
class Products;
}

struct spimsNames{
    QString name;
    QSpinBox* spin;
    QLabel* labelImg;
    QString rut;
};

class Products : public QDialog
{
    Q_OBJECT

public:
    explicit Products(QWidget *parent = nullptr);
    ~Products();

private slots:
    void on_addCart_clicked();
    void on_returnP1_clicked();

private:
    Ui::Products *ui;

    QVector <spimsNames> spins;
    QMap <QString, int> productsCant;
    bool validateCart;
    void buttonChangeColor();
};

#endif // PRODUCTS_H
