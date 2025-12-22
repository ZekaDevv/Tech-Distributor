#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QJsonArray>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_newUser_clicked();

    void on_joinAdmin_clicked();

    void on_bottonIng_clicked();

private:
    Ui::MainWindow *ui;

    QJsonArray arrUsers;
    QJsonArray arrUsersAdmins;

    bool isAdmin;

    bool logIn(const QJsonArray &arr);
    void loadData(QJsonArray &arr, const QString &fileName);
    void createDefaultAdmin();
};

#endif // MAINWINDOW_H
