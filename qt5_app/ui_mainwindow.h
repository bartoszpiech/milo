/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <viewer.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton;
    QTabWidget *tabWidget;
    QWidget *main_page;
    QTextEdit *textEdit;
    QWidget *configuration_page;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QFormLayout *formLayout;
    QPushButton *pushButton_search;
    QComboBox *comboBox_device_list;
    QPushButton *pushButton_connect;
    QPushButton *pushButton_disconnect;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout;
    QTextEdit *textEdit_logs;
    QWidget *charts_page;
    QWidget *visualization_page;
    QGridLayout *gridLayout_2;
    Viewer *widget;
    QMenuBar *menubar;
    QMenu *menuCommunication;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1320, 782);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 2, 2, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 2, 0, 1, 1);

        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy);
        pushButton->setMaximumSize(QSize(80, 30));

        gridLayout->addWidget(pushButton, 2, 1, 1, 1);

        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setMinimumSize(QSize(0, 0));
        main_page = new QWidget();
        main_page->setObjectName(QString::fromUtf8("main_page"));
        textEdit = new QTextEdit(main_page);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setGeometry(QRect(10, 10, 651, 71));
        tabWidget->addTab(main_page, QString());
        configuration_page = new QWidget();
        configuration_page->setObjectName(QString::fromUtf8("configuration_page"));
        verticalLayout = new QVBoxLayout(configuration_page);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        groupBox = new QGroupBox(configuration_page);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setMinimumSize(QSize(0, 0));
        groupBox->setMaximumSize(QSize(16777215, 100));
        formLayout = new QFormLayout(groupBox);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        pushButton_search = new QPushButton(groupBox);
        pushButton_search->setObjectName(QString::fromUtf8("pushButton_search"));

        formLayout->setWidget(0, QFormLayout::LabelRole, pushButton_search);

        comboBox_device_list = new QComboBox(groupBox);
        comboBox_device_list->setObjectName(QString::fromUtf8("comboBox_device_list"));

        formLayout->setWidget(0, QFormLayout::FieldRole, comboBox_device_list);

        pushButton_connect = new QPushButton(groupBox);
        pushButton_connect->setObjectName(QString::fromUtf8("pushButton_connect"));

        formLayout->setWidget(1, QFormLayout::LabelRole, pushButton_connect);

        pushButton_disconnect = new QPushButton(groupBox);
        pushButton_disconnect->setObjectName(QString::fromUtf8("pushButton_disconnect"));

        formLayout->setWidget(1, QFormLayout::FieldRole, pushButton_disconnect);


        verticalLayout->addWidget(groupBox);

        groupBox_2 = new QGroupBox(configuration_page);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        horizontalLayout = new QHBoxLayout(groupBox_2);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        textEdit_logs = new QTextEdit(groupBox_2);
        textEdit_logs->setObjectName(QString::fromUtf8("textEdit_logs"));

        horizontalLayout->addWidget(textEdit_logs);


        verticalLayout->addWidget(groupBox_2);

        tabWidget->addTab(configuration_page, QString());
        charts_page = new QWidget();
        charts_page->setObjectName(QString::fromUtf8("charts_page"));
        tabWidget->addTab(charts_page, QString());
        visualization_page = new QWidget();
        visualization_page->setObjectName(QString::fromUtf8("visualization_page"));
        gridLayout_2 = new QGridLayout(visualization_page);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        widget = new Viewer(visualization_page);
        widget->setObjectName(QString::fromUtf8("widget"));

        gridLayout_2->addWidget(widget, 0, 0, 1, 1);

        tabWidget->addTab(visualization_page, QString());

        gridLayout->addWidget(tabWidget, 0, 0, 1, 3);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setEnabled(true);
        menubar->setGeometry(QRect(0, 0, 1320, 22));
        menuCommunication = new QMenu(menubar);
        menuCommunication->setObjectName(QString::fromUtf8("menuCommunication"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        statusbar->setEnabled(true);
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuCommunication->menuAction());

        retranslateUi(MainWindow);
        QObject::connect(pushButton, SIGNAL(clicked()), MainWindow, SLOT(close()));

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "Close", nullptr));
        textEdit->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans Serif'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:36pt;\">&quot;MiLo&quot; robot arm visualisation</span></p></body></html>", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(main_page), QCoreApplication::translate("MainWindow", "Main Page", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "Connection", nullptr));
        pushButton_search->setText(QCoreApplication::translate("MainWindow", "Search", nullptr));
        pushButton_connect->setText(QCoreApplication::translate("MainWindow", "Connect", nullptr));
        pushButton_disconnect->setText(QCoreApplication::translate("MainWindow", "Disconnect", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "UART", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(configuration_page), QCoreApplication::translate("MainWindow", "Configuration", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(charts_page), QCoreApplication::translate("MainWindow", "Charts", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(visualization_page), QCoreApplication::translate("MainWindow", "Visualization", nullptr));
        menuCommunication->setTitle(QCoreApplication::translate("MainWindow", "Communication", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
