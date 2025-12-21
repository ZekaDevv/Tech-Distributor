#include "products.h"
#include "ui_products.h"
#include "shoppingcart.h"
#include <QMap>
#include <QVector>
#include <QPropertyAnimation>

Products::Products(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Products)
{
    ui->setupUi(this);

    spins.append({"Mouse", ui->cantMouse, ui->imageMouse, ":/new/images/image/mouse.jpg"});
    spins.append({"Teclado", ui->cantKey, ui->imageKey, ":/new/images/image/key.jpg"});
    spins.append({"Audifono", ui->cantHeadph, ui->imageHeadph, ":/new/images/image/headPF.jpg"});
    spins.append({"Monitor", ui->cantMonitor, ui->imageMonitor, ":/new/images/image/monitor.jpg"});
    spins.append({"Laptop", ui->cantPC,ui->imageLaptop, ":/new/images/image/laptop.jpg"});
    spins.append({"PC", ui->cantLaptop, ui->imagePC, ":/new/images/image/PC.jpg"});

    for (int i = 0; i < spins.size(); i++) {
        QPixmap imagen(spins[i].rut);
        QPixmap imageScale = imagen.scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation);

        spins[i].labelImg->setPixmap(imageScale);

        spins[i].labelImg->setAlignment(Qt::AlignCenter);
    }

    buttonChangeColor();
    validateCart = false;
}

Products::~Products()
{
    delete ui;
}

void Products::buttonChangeColor() {
    if(productsCant.empty()){

        ui->buttonShoppingCart->setIcon(QIcon(":/new/images/image/car_black.png"));
        ui->buttonShoppingCart->setIconSize(QSize(25, 25));

    } else {

        if(!validateCart) {
            ui->buttonShoppingCart->setIcon(QIcon(":/new/images/image/car_green.png"));
            validateCart = true;
        }

        QPropertyAnimation *animacion = new QPropertyAnimation(ui->buttonShoppingCart, "iconSize");
        animacion->setDuration(400);

        animacion->setKeyValueAt(0, QSize(25, 25));
        animacion->setKeyValueAt(0.5, QSize(30, 30));
        animacion->setKeyValueAt(1, QSize(25, 25));

        animacion->start(QAbstractAnimation::DeleteWhenStopped);
    }
}

void Products::on_addCart_clicked() {
    bool validateCant = false;

    for (int i = 0; i < spins.size(); ++i) {
        int cant = spins[i].spin->value();
        QString name = spins[i].name;

        if (cant > 0) {
            productsCant[name] += cant;
            validateCant = true;
        }

        spins[i].spin->setValue(0);
    }
    if(!productsCant.empty()) ui->label_error->clear();

    if(validateCant) buttonChangeColor();
}

void Products::on_returnP1_clicked() {
    this->close();
}

void Products::on_buttonShoppingCart_clicked() {
    shoppingCart WindowShoppingCart(productsCant);
    if(validateCart) {
        this->setWindowOpacity(0.5);
        WindowShoppingCart.setModal(true);
        WindowShoppingCart.exec();
        this->setWindowOpacity(1.0);

        productsCant = {};
        ui->buttonShoppingCart->setIcon(QIcon(":/new/images/image/car_black.png"));
        ui->buttonShoppingCart->setIconSize(QSize(25, 25));
        validateCart = false;

    }else {
        ui->label_error->setText("Debes ingresar productos al carrito de compras para acceder");
    }
}
