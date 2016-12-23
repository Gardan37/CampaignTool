/********************************************************************************
** Form generated from reading UI file 'campaigntool.ui'
**
** Created: Thu Oct 11 22:23:13 2012
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CAMPAIGNTOOL_H
#define UI_CAMPAIGNTOOL_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QTableView>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CampaignTool
{
public:
    QWidget *centralWidget;
    QTableView *strategicView;
    QPushButton *closeButton;
    QTableView *tacticalView;
    QLabel *strategicLabel;
    QLabel *tacticalLabel;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *CampaignTool)
    {
        if (CampaignTool->objectName().isEmpty())
            CampaignTool->setObjectName(QString::fromUtf8("CampaignTool"));
        CampaignTool->resize(1200, 1000);
        centralWidget = new QWidget(CampaignTool);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        strategicView = new QTableView(centralWidget);
        strategicView->setObjectName(QString::fromUtf8("strategicView"));
        strategicView->setGeometry(QRect(10, 30, 1140, 680));
        strategicView->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        strategicView->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        closeButton = new QPushButton(centralWidget);
        closeButton->setObjectName(QString::fromUtf8("closeButton"));
        closeButton->setGeometry(QRect(550, 800, 105, 24));
        tacticalView = new QTableView(centralWidget);
        tacticalView->setObjectName(QString::fromUtf8("tacticalView"));
        tacticalView->setGeometry(QRect(10, 750, 530, 180));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tacticalView->sizePolicy().hasHeightForWidth());
        tacticalView->setSizePolicy(sizePolicy);
        tacticalView->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        tacticalView->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        tacticalView->setWordWrap(false);
        strategicLabel = new QLabel(centralWidget);
        strategicLabel->setObjectName(QString::fromUtf8("strategicLabel"));
        strategicLabel->setGeometry(QRect(20, 10, 371, 16));
        tacticalLabel = new QLabel(centralWidget);
        tacticalLabel->setObjectName(QString::fromUtf8("tacticalLabel"));
        tacticalLabel->setGeometry(QRect(20, 720, 231, 16));
        CampaignTool->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(CampaignTool);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1200, 21));
        CampaignTool->setMenuBar(menuBar);
        mainToolBar = new QToolBar(CampaignTool);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        CampaignTool->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(CampaignTool);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        CampaignTool->setStatusBar(statusBar);

        retranslateUi(CampaignTool);

        QMetaObject::connectSlotsByName(CampaignTool);
    } // setupUi

    void retranslateUi(QMainWindow *CampaignTool)
    {
        CampaignTool->setWindowTitle(QApplication::translate("CampaignTool", "CampaignTool", 0, QApplication::UnicodeUTF8));
        closeButton->setText(QApplication::translate("CampaignTool", "Close", 0, QApplication::UnicodeUTF8));
        strategicLabel->setText(QApplication::translate("CampaignTool", "Strategic Map", 0, QApplication::UnicodeUTF8));
        tacticalLabel->setText(QApplication::translate("CampaignTool", "Tactical Map", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class CampaignTool: public Ui_CampaignTool {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CAMPAIGNTOOL_H
