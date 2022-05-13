/********************************************************************************
** Form generated from reading UI file 'VisualLab2.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VISUALLAB2_H
#define UI_VISUALLAB2_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_VisualLab2Class
{
public:
    QWidget *centralWidget;
    QPushButton *pushButton;
    QPushButton *button_matching;
    QPushButton *button_firstMatrix;
    QPushButton *button_3d;
    QPushButton *button_secondMatrix;
    QPushButton *button_startCalculate;
    QFrame *line;
    QFrame *line_2;
    QFrame *line_3;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *VisualLab2Class)
    {
        if (VisualLab2Class->objectName().isEmpty())
            VisualLab2Class->setObjectName(QString::fromUtf8("VisualLab2Class"));
        VisualLab2Class->resize(1043, 195);
        centralWidget = new QWidget(VisualLab2Class);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(10, 10, 111, 41));
        button_matching = new QPushButton(centralWidget);
        button_matching->setObjectName(QString::fromUtf8("button_matching"));
        button_matching->setGeometry(QRect(470, 10, 201, 41));
        button_firstMatrix = new QPushButton(centralWidget);
        button_firstMatrix->setObjectName(QString::fromUtf8("button_firstMatrix"));
        button_firstMatrix->setGeometry(QRect(160, 60, 281, 31));
        button_3d = new QPushButton(centralWidget);
        button_3d->setObjectName(QString::fromUtf8("button_3d"));
        button_3d->setGeometry(QRect(700, 10, 331, 41));
        button_secondMatrix = new QPushButton(centralWidget);
        button_secondMatrix->setObjectName(QString::fromUtf8("button_secondMatrix"));
        button_secondMatrix->setGeometry(QRect(160, 100, 281, 31));
        button_startCalculate = new QPushButton(centralWidget);
        button_startCalculate->setObjectName(QString::fromUtf8("button_startCalculate"));
        button_startCalculate->setGeometry(QRect(160, 10, 291, 41));
        line = new QFrame(centralWidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(130, 0, 20, 131));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);
        line_2 = new QFrame(centralWidget);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setGeometry(QRect(450, 0, 20, 131));
        line_2->setFrameShape(QFrame::VLine);
        line_2->setFrameShadow(QFrame::Sunken);
        line_3 = new QFrame(centralWidget);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        line_3->setGeometry(QRect(673, 0, 20, 131));
        line_3->setFrameShape(QFrame::VLine);
        line_3->setFrameShadow(QFrame::Sunken);
        VisualLab2Class->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(VisualLab2Class);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1043, 26));
        VisualLab2Class->setMenuBar(menuBar);
        mainToolBar = new QToolBar(VisualLab2Class);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        VisualLab2Class->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(VisualLab2Class);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        VisualLab2Class->setStatusBar(statusBar);

        retranslateUi(VisualLab2Class);

        QMetaObject::connectSlotsByName(VisualLab2Class);
    } // setupUi

    void retranslateUi(QMainWindow *VisualLab2Class)
    {
        VisualLab2Class->setWindowTitle(QCoreApplication::translate("VisualLab2Class", "VisualLab2", nullptr));
        pushButton->setText(QCoreApplication::translate("VisualLab2Class", "Open Figures", nullptr));
        button_matching->setText(QCoreApplication::translate("VisualLab2Class", "Option A: Matching Only", nullptr));
        button_firstMatrix->setText(QCoreApplication::translate("VisualLab2Class", "Calculate First projection matrix", nullptr));
        button_3d->setText(QCoreApplication::translate("VisualLab2Class", "Option B: Matching and 3D reconstruction", nullptr));
        button_secondMatrix->setText(QCoreApplication::translate("VisualLab2Class", "Calculate Second projection matrix", nullptr));
        button_startCalculate->setText(QCoreApplication::translate("VisualLab2Class", "Start calaulate projection matrics:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class VisualLab2Class: public Ui_VisualLab2Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VISUALLAB2_H
