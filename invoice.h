#ifndef INVOICE_H
#define INVOICE_H

#include <QDialog>

namespace Ui {
class invoice;
}

class invoice : public QDialog
{
    Q_OBJECT

public:
    explicit invoice(QWidget *parent = nullptr);
    ~invoice();

private:
    Ui::invoice *ui;
};

#endif // INVOICE_H
