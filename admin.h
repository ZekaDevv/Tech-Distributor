#ifndef ADMIN_H
#define ADMIN_H

#include <QDialog>
#include "QJsonArray"
#include <QTableWidgetItem>

namespace Ui {
class admin;
}

class admin : public QDialog
{
    Q_OBJECT

public:
    explicit admin(QWidget *parent = nullptr);
    ~admin();

private slots:
    void on_returnP1_clicked();

    void on_addCart_clicked();

private:
    Ui::admin *ui;

    QString filePath;
    QJsonArray arrProducts;

    void createListProducts();
    void checkProductsFile();
    void loadProductsTable();
    void onTableItemChanged(QTableWidgetItem *item);
};

#endif // ADMIN_H
