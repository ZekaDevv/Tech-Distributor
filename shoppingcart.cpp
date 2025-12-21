#include "shoppingcart.h"
#include "ui_shoppingcart.h"
#include "invoice.h"
#include <QString>
#include <algorithm>

shoppingCart::shoppingCart(QMap <QString, int> productsCant, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::shoppingCart)
{
    ui->setupUi(this);

    ui->orderUp->setIcon(QIcon(":/new/images/image/arrowUp.png"));
    ui->orderUp->setIconSize(QSize(20, 20));

    ui->orderDown->setIcon(QIcon(":/new/images/image/arrowDown.png"));
    ui->orderDown->setIconSize(QSize(20, 20));

    ui->resetTable->setIcon(QIcon(":/new/images/image/loading-arrow.png"));
    ui->resetTable->setIconSize(QSize(20, 20));

    productsCantt = productsCant;
    productsPrice = {
        {"Mouse", 12},
        {"Teclado", 20},
        {"Audifono", 25},
        {"Monitor", 75},
        {"PC",180},
        {"Laptop", 300}
    };

    int totalPrice;

    for (auto [name, cant] : productsCantt.asKeyValueRange()) {
        int price = productsPrice[name];
        int priceTotal = price * cant;
        products.push_back({name, price, cant, priceTotal});
        totalPrice += priceTotal;
    }

    ui->tableProducts->setRowCount(products.size());
    ui->tableProducts->setColumnCount(4);

    ui->tableProducts->verticalHeader()->setVisible(false);

    QStringList titles;
    titles << "Nombre" << "Precio Unitario" << "Cantidad" << "Precio Total";
    ui->tableProducts->setHorizontalHeaderLabels(titles);

    ui->tableProducts->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);


    ui->printPrice->setText("$" + QString::number(totalPrice));

    insertionTable(products);
}

shoppingCart::~shoppingCart()
{
    delete ui;
}

void shoppingCart::insertionTable (const QVector <shoppingCart::productInfo> &items) {
    for (int i = 0; i < items.size(); i++) {
        QTableWidgetItem *itemName = new QTableWidgetItem(items[i].name);
        QTableWidgetItem *itemPrice = new QTableWidgetItem("$" + QString::number(items[i].price));
        QTableWidgetItem *itemCant = new QTableWidgetItem(QString::number(items[i].cant));
        QTableWidgetItem *itemTotalPrice = new QTableWidgetItem("$" + QString::number(items[i].priceTotal));

        ui->tableProducts->setItem(i, 0, itemName);
        ui->tableProducts->setItem(i, 1, itemPrice);
        ui->tableProducts->setItem(i, 2, itemCant);
        ui->tableProducts->setItem(i, 3, itemTotalPrice);
    }
}

bool SequentialSearch (const QString &input, const QString &product) {

    if(input.length() > product.length()) return false;

    for (int i = 0; i <= (product.length() - input.length()); i++) {
        bool match = true;

        for (int j = 0; j < input.length(); j++) {

            if(product[i + j] != input[j]){
                match = false;
                break;
            }
        }

        if(match) return true;
    }

    return false;
}

QVector <shoppingCart::productInfo> shoppingCart::selectionSort (const QVector <shoppingCart::productInfo> &products, const bool orde) {
    QVector <shoppingCart::productInfo> productsSorting = products;

    int temp, min;

    for (int i = 0; i < productsSorting.size(); i++) {
        min = i;

        for (int j = i + 1; j < productsSorting.size(); j++) {

            if(productsSorting[j].priceTotal < productsSorting[min].priceTotal) min = j;

        }

        shoppingCart::productInfo temp = productsSorting[i];
        productsSorting[i] = productsSorting[min];
        productsSorting[min] = temp;

    }

    if(orde) std::reverse(productsSorting.begin(), productsSorting.end());

    return productsSorting;
}

void shoppingCart::on_filterInput_textChanged(const QString &arg1) {
    QString inputLow = arg1.toLower();
    inputLow.remove(" ");

    if(inputLow.isEmpty()){
        for (int i = 0; i < products.size(); ++i) {
                ui->tableProducts->setRowHidden(i, false);
        }
        return;
    }

    for (int i = 0; i < products.size(); ++i) {
        QString productLow = products[i].name.toLower();
        bool validation = SequentialSearch(inputLow, productLow);

        if(validation) {
            ui->tableProducts->setRowHidden(i, false);
        }else {
            ui->tableProducts->setRowHidden(i, true);
        }
    }

}


void shoppingCart::on_orderDown_clicked() {
    insertionTable(selectionSort(products, false));
}

void shoppingCart::on_orderUp_clicked() {
    insertionTable(selectionSort(products, true));
}

void shoppingCart::on_resetTable_clicked(){
    insertionTable(products);
}

void shoppingCart::on_buttonBack_clicked() {
    this->close();
}

void shoppingCart::on_buttonBuy_clicked() {
    invoice windowsInvoice;

    this->setWindowOpacity(0.5);
    windowsInvoice.setModal(true);
    windowsInvoice.exec();
    this->setWindowOpacity(1.0);

    this->close();
}

