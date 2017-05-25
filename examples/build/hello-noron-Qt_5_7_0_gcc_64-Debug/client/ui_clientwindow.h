/********************************************************************************
** Form generated from reading UI file 'clientwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLIENTWINDOW_H
#define UI_CLIENTWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ClientWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_4;
    QLineEdit *lineEdit;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButtonGetRandomNumber;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label_3;
    QSpinBox *spinBox;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButtonGetRandomNumberWithTimeout;
    QLabel *labelResult;
    QSpacerItem *verticalSpacer;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *ClientWindow)
    {
        if (ClientWindow->objectName().isEmpty())
            ClientWindow->setObjectName(QStringLiteral("ClientWindow"));
        ClientWindow->resize(299, 330);
        centralwidget = new QWidget(ClientWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        verticalLayout_2 = new QVBoxLayout(centralwidget);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        verticalLayout_2->addWidget(label_4);

        lineEdit = new QLineEdit(centralwidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        verticalLayout_2->addWidget(lineEdit);

        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        horizontalLayout_3 = new QHBoxLayout(groupBox);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalSpacer_2 = new QSpacerItem(168, 17, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);

        pushButtonGetRandomNumber = new QPushButton(groupBox);
        pushButtonGetRandomNumber->setObjectName(QStringLiteral("pushButtonGetRandomNumber"));

        horizontalLayout_3->addWidget(pushButtonGetRandomNumber);


        verticalLayout_2->addWidget(groupBox);

        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        verticalLayout = new QVBoxLayout(groupBox_2);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout->addWidget(label_3);

        spinBox = new QSpinBox(groupBox_2);
        spinBox->setObjectName(QStringLiteral("spinBox"));

        horizontalLayout->addWidget(spinBox);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        pushButtonGetRandomNumberWithTimeout = new QPushButton(groupBox_2);
        pushButtonGetRandomNumberWithTimeout->setObjectName(QStringLiteral("pushButtonGetRandomNumberWithTimeout"));

        horizontalLayout_2->addWidget(pushButtonGetRandomNumberWithTimeout);


        verticalLayout->addLayout(horizontalLayout_2);


        verticalLayout_2->addWidget(groupBox_2);

        labelResult = new QLabel(centralwidget);
        labelResult->setObjectName(QStringLiteral("labelResult"));
        QFont font;
        font.setPointSize(17);
        labelResult->setFont(font);

        verticalLayout_2->addWidget(labelResult);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        ClientWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(ClientWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 299, 19));
        ClientWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(ClientWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        ClientWindow->setStatusBar(statusbar);

        retranslateUi(ClientWindow);

        QMetaObject::connectSlotsByName(ClientWindow);
    } // setupUi

    void retranslateUi(QMainWindow *ClientWindow)
    {
        ClientWindow->setWindowTitle(QApplication::translate("ClientWindow", "RPC Chat client", 0));
        label_4->setText(QApplication::translate("ClientWindow", "Username", 0));
        groupBox->setTitle(QApplication::translate("ClientWindow", "Get random number", 0));
        pushButtonGetRandomNumber->setText(QApplication::translate("ClientWindow", "Get", 0));
        groupBox_2->setTitle(QApplication::translate("ClientWindow", "Get random number with timeout", 0));
        label_3->setText(QApplication::translate("ClientWindow", "Timeout", 0));
        pushButtonGetRandomNumberWithTimeout->setText(QApplication::translate("ClientWindow", "Get", 0));
        labelResult->setText(QApplication::translate("ClientWindow", "Press Get button...", 0));
    } // retranslateUi

};

namespace Ui {
    class ClientWindow: public Ui_ClientWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLIENTWINDOW_H
