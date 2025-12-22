#include "admin.h"
#include "ui_admin.h"
#include "modalmsh.h"
#include "QJsonArray"
#include <QMap>
#include "QJsonObject"
#include <QJsonDocument>
#include <QFile>
#include <QStandardPaths>
#include <QDir>
#include <QDebug>

admin::admin(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::admin)
{
    ui->setupUi(this);

    checkProductsFile();

    QStringList titulos;
    titulos << "Nombre" << "Precio" << "Stock";

    ui->productsTable->setColumnCount(3);
    ui->productsTable->setHorizontalHeaderLabels(titulos);

    ui->productsTable->blockSignals(true);

    loadProductsTable();

    ui->productsTable->blockSignals(false);

    connect(ui->productsTable, &QTableWidget::itemChanged,
            this, &admin::onTableItemChanged);
}

admin::~admin()
{
    delete ui;
}

void admin::on_returnP1_clicked()
{
    this->close();
}

void admin::createListProducts() {
    QMap <QString, double> productsPrice = {
        {"Mouse", 12},
        {"Teclado", 20},
        {"Audifono", 25},
        {"Monitor", 75},
        {"PC", 180},
        {"Laptop", 300}
    };

    arrProducts = QJsonArray();

    for (auto [name, price] : productsPrice.asKeyValueRange()) {
        QJsonObject obj;
        obj["name"] = name;
        obj["price"] = price;
        obj["stock"] = 0;
        arrProducts.append(obj);
    }
}


void admin::checkProductsFile() {
    QString path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir dir(path);
    if (!dir.exists()) dir.mkpath(".");
    filePath = dir.filePath("products.json");;

    QFile file(filePath);

    if(!file.exists()) {
        createListProducts();

        if (file.open(QIODevice::WriteOnly)) {
            QJsonDocument doc(arrProducts);
            file.write(doc.toJson());
            file.close();
        }
        return;
    }


    if(file.open(QIODevice::ReadOnly)) {
        QByteArray data = file.readAll();
        QJsonDocument doc = QJsonDocument::fromJson(data);
        file.close();

        if(doc.isEmpty() || !doc.isArray()) {
            createListProducts();

            if (file.open(QIODevice::WriteOnly)) {
                QJsonDocument doc(arrProducts);
                file.write(doc.toJson());
                file.close();
            }
        }else {
            arrProducts = doc.array();
            file.close();
        }
    }
}


void admin::loadProductsTable() {
    ui->productsTable->setRowCount(0);

    for (const auto &item : arrProducts) {
        QJsonObject obj = item.toObject();

        int row = ui->productsTable->rowCount();
        ui->productsTable->insertRow(row);

        QTableWidgetItem *itemName = new QTableWidgetItem(obj["name"].toString());
        itemName->setFlags(itemName->flags() ^ Qt::ItemIsEditable);
        ui->productsTable->setItem(row, 0, itemName);

        double price = obj["price"].toDouble();
        ui->productsTable->setItem(row, 1, new QTableWidgetItem(QString::number(price)));

        double stock = obj["stock"].toInt();
        ui->productsTable->setItem(row, 2, new QTableWidgetItem(QString::number(stock)));
    }
}


void admin::onTableItemChanged(QTableWidgetItem *item) {
    if (!item) return;

    int row = item->row();
    int col = item->column();

    QJsonObject objOrigin = arrProducts[row].toObject();

    QString strOrigin;
    QString strNew = item->text();

    if (col == 0) return;

    if (col == 1) { // Price
        strOrigin = QString::number(objOrigin["price"].toDouble());
    }
    else if (col == 2) { // Stock
        strOrigin = QString::number(objOrigin["stock"].toInt());
    }

    if (strNew != strOrigin) {
        item->setBackground(QColor(200, 255, 200));
        item->setToolTip("Valor original: " + strOrigin);
    } else {
        item->setBackground(Qt::white);
        item->setToolTip("");
    }
}


void admin::on_addCart_clicked() {
    QJsonArray newArr;
    bool isChanges = false;

    int rows = ui->productsTable->rowCount();

    for (int i = 0; i < rows; i++) {
        QJsonObject obj;
        QJsonObject originalObj = arrProducts[i].toObject();

        QString name = ui->productsTable->item(i, 0)->text();
        double price = ui->productsTable->item(i, 1)->text().toDouble();
        int stock = ui->productsTable->item(i, 2)->text().toInt();

        obj["name"] = name;
        obj["price"] = price;
        obj["stock"] = stock;

        newArr.append(obj);

        double orgPrice = originalObj["price"].toDouble();
        int orgStock = originalObj["stock"].toInt();

        if (price != orgPrice || stock != orgStock) {
            isChanges = true;
        }
    }

    if (!isChanges) {
        ui->label_error->setText("No se detectaron cambios");
        return;
    }

    QFile file(filePath);

    if (file.open(QIODevice::WriteOnly)) {
        QJsonDocument doc(newArr);
        file.write(doc.toJson());
        file.close();

        arrProducts = newArr;

        ui->productsTable->blockSignals(true);
        for(int i = 0; i < ui->productsTable->rowCount(); i++) {
            ui->productsTable->item(i, 1)->setBackground(Qt::white);
            ui->productsTable->item(i, 2)->setBackground(Qt::white);
        }
        ui->productsTable->blockSignals(false);

        modalMsh windowModalMsh("Cambios guardados");
        windowModalMsh.setModal(true);
        windowModalMsh.exec();

    }
}
