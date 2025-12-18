/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *title;
    QLabel *label_psw;
    QLineEdit *input_psw;
    QLabel *label_user;
    QLineEdit *input_user;
    QPushButton *bottonIng;
    QLabel *label_admin;
    QLabel *label_ne_user;
    QLabel *label_error;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(375, 357);
        MainWindow->setStyleSheet(QString::fromUtf8("background-color: rgb(246, 245, 244);"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        title = new QLabel(centralwidget);
        title->setObjectName("title");
        title->setGeometry(QRect(80, 30, 231, 41));
        title->setStyleSheet(QString::fromUtf8("color: rgb(53, 132, 228);\n"
"font: 500 20pt \"Ubuntu Sans\";"));
        title->setAlignment(Qt::AlignmentFlag::AlignCenter);
        label_psw = new QLabel(centralwidget);
        label_psw->setObjectName("label_psw");
        label_psw->setGeometry(QRect(140, 160, 101, 18));
        label_psw->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"font: 14pt \"Ubuntu Sans\";"));
        input_psw = new QLineEdit(centralwidget);
        input_psw->setObjectName("input_psw");
        input_psw->setGeometry(QRect(80, 190, 221, 26));
        input_psw->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        label_user = new QLabel(centralwidget);
        label_user->setObjectName("label_user");
        label_user->setGeometry(QRect(160, 90, 81, 18));
        label_user->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"font: 14pt \"Ubuntu Sans\";"));
        input_user = new QLineEdit(centralwidget);
        input_user->setObjectName("input_user");
        input_user->setGeometry(QRect(80, 120, 221, 26));
        input_user->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        bottonIng = new QPushButton(centralwidget);
        bottonIng->setObjectName("bottonIng");
        bottonIng->setGeometry(QRect(140, 270, 94, 26));
        bottonIng->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        label_admin = new QLabel(centralwidget);
        label_admin->setObjectName("label_admin");
        label_admin->setGeometry(QRect(80, 240, 191, 18));
        label_admin->setStyleSheet(QString::fromUtf8("color: rgb(0, 41, 255);\n"
"font: 8pt \"Ubuntu Sans\";"));
        label_ne_user = new QLabel(centralwidget);
        label_ne_user->setObjectName("label_ne_user");
        label_ne_user->setGeometry(QRect(80, 220, 201, 18));
        label_ne_user->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"color: rgb(0, 41, 255);\n"
"font: 8pt \"Ubuntu Sans\";"));
        label_error = new QLabel(centralwidget);
        label_error->setObjectName("label_error");
        label_error->setGeometry(QRect(70, 300, 231, 18));
        label_error->setStyleSheet(QString::fromUtf8("color: rgb(224, 27, 36);\n"
"font: 8pt \"Ubuntu Sans\";"));
        label_error->setAlignment(Qt::AlignmentFlag::AlignCenter);
        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Tech Distributor", nullptr));
        title->setText(QCoreApplication::translate("MainWindow", "Tech Distributor", nullptr));
        label_psw->setText(QCoreApplication::translate("MainWindow", "Contrase\303\261a", nullptr));
        label_user->setText(QCoreApplication::translate("MainWindow", "Usuario", nullptr));
        bottonIng->setText(QCoreApplication::translate("MainWindow", "Ingresar", nullptr));
        label_admin->setText(QCoreApplication::translate("MainWindow", "Ingrear como Administrador", nullptr));
        label_ne_user->setText(QCoreApplication::translate("MainWindow", "No posees Usuario? Click aqui\314\201", nullptr));
        label_error->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
