#ifndef MODALMSH_H
#define MODALMSH_H

#include <QDialog>

namespace Ui {
class modalMsh;
}

class modalMsh : public QDialog
{
    Q_OBJECT

public:
    explicit modalMsh(const QString &title,QWidget *parent = nullptr);
    ~modalMsh();

private slots:
    void on_continueProgram_clicked();

private:
    Ui::modalMsh *ui;
};

#endif // MODALMSH_H
