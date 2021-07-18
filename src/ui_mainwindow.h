/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "tabbededitor.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionNew;
    QAction *actionOpen;
    QAction *actionSave;
    QAction *actionSave_As;
    QAction *actionPrint;
    QAction *actionExit;
    QAction *actionUndo;
    QAction *actionCut;
    QAction *actionCopy;
    QAction *actionPaste;
    QAction *actionFind;
    QAction *actionReplace;
    QAction *actionGo_To;
    QAction *actionSelect_All;
    QAction *actionTime_Date;
    QAction *actionFont;
    QAction *actionStatus_Bar;
    QAction *actionRedo;
    QAction *actionAuto_Indent;
    QAction *actionWord_Wrap;
    QAction *actionC_Lang;
    QAction *actionCPP_Lang;
    QAction *actionJava_Lang;
    QAction *actionPython_Lang;
    QAction *actionTool_Bar;
    QWidget *centralWidget;
    TabbedEditor *tabWidget;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QComboBox *comboBox;
    QLabel *label_7;
    QComboBox *comboBox_4;
    QStackedWidget *stackedWidget;
    QWidget *page_3;
    QWidget *page;
    QLabel *label_2;
    QPushButton *pushButton;
    QLineEdit *lineEdit_9;
    QWidget *page_2;
    QVBoxLayout *verticalLayout;
    QLabel *label_3;
    QLineEdit *lineEdit;
    QLabel *label_4;
    QLineEdit *lineEdit_2;
    QLabel *label_5;
    QLineEdit *lineEdit_3;
    QHBoxLayout *horizontalLayout;
    QPushButton *Connect_Button;
    QPushButton *Disconnect_Button;
    QStackedWidget *stackedWidget_2;
    QWidget *page_7;
    QWidget *page_6;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_6;
    QLineEdit *lineEdit_7;
    QPushButton *Load_Button;
    QLabel *label_11;
    QLineEdit *lineEdit_8;
    QPushButton *Upload_Button;
    QWidget *page_8;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_8;
    QLineEdit *lineEdit_4;
    QLabel *label_10;
    QLineEdit *lineEdit_6;
    QPushButton *pushButton_2;
    QWidget *page_9;
    QVBoxLayout *verticalLayout_5;
    QLabel *label_9;
    QLineEdit *lineEdit_5;
    QPushButton *pushButton_3;
    QTabWidget *tabWidget_2;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuEdit;
    QMenu *menuFormat;
    QMenu *menuLanguage;
    QMenu *menuView;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QToolBar *toolBar;
    QToolBar *toolBar_2;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(922, 639);
        MainWindow->setMinimumSize(QSize(530, 230));
        actionNew = new QAction(MainWindow);
        actionNew->setObjectName(QString::fromUtf8("actionNew"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/res/icons/new.bmp"), QSize(), QIcon::Normal, QIcon::On);
        actionNew->setIcon(icon);
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icons/res/icons/folder.bmp"), QSize(), QIcon::Normal, QIcon::On);
        actionOpen->setIcon(icon1);
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName(QString::fromUtf8("actionSave"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/icons/res/icons/save.bmp"), QSize(), QIcon::Normal, QIcon::On);
        actionSave->setIcon(icon2);
        actionSave_As = new QAction(MainWindow);
        actionSave_As->setObjectName(QString::fromUtf8("actionSave_As"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/icons/res/icons/save-as.bmp"), QSize(), QIcon::Normal, QIcon::On);
        actionSave_As->setIcon(icon3);
        actionPrint = new QAction(MainWindow);
        actionPrint->setObjectName(QString::fromUtf8("actionPrint"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/icons/res/icons/printer.bmp"), QSize(), QIcon::Normal, QIcon::On);
        actionPrint->setIcon(icon4);
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        actionUndo = new QAction(MainWindow);
        actionUndo->setObjectName(QString::fromUtf8("actionUndo"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/icons/res/icons/undo.bmp"), QSize(), QIcon::Normal, QIcon::On);
        actionUndo->setIcon(icon5);
        actionCut = new QAction(MainWindow);
        actionCut->setObjectName(QString::fromUtf8("actionCut"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/icons/res/icons/cut.bmp"), QSize(), QIcon::Normal, QIcon::On);
        actionCut->setIcon(icon6);
        actionCopy = new QAction(MainWindow);
        actionCopy->setObjectName(QString::fromUtf8("actionCopy"));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/icons/res/icons/copy.bmp"), QSize(), QIcon::Normal, QIcon::On);
        actionCopy->setIcon(icon7);
        actionPaste = new QAction(MainWindow);
        actionPaste->setObjectName(QString::fromUtf8("actionPaste"));
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/icons/res/icons/paste.bmp"), QSize(), QIcon::Normal, QIcon::On);
        actionPaste->setIcon(icon8);
        actionFind = new QAction(MainWindow);
        actionFind->setObjectName(QString::fromUtf8("actionFind"));
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/icons/res/icons/search.bmp"), QSize(), QIcon::Normal, QIcon::On);
        actionFind->setIcon(icon9);
        actionReplace = new QAction(MainWindow);
        actionReplace->setObjectName(QString::fromUtf8("actionReplace"));
        actionGo_To = new QAction(MainWindow);
        actionGo_To->setObjectName(QString::fromUtf8("actionGo_To"));
        actionSelect_All = new QAction(MainWindow);
        actionSelect_All->setObjectName(QString::fromUtf8("actionSelect_All"));
        actionTime_Date = new QAction(MainWindow);
        actionTime_Date->setObjectName(QString::fromUtf8("actionTime_Date"));
        actionFont = new QAction(MainWindow);
        actionFont->setObjectName(QString::fromUtf8("actionFont"));
        actionStatus_Bar = new QAction(MainWindow);
        actionStatus_Bar->setObjectName(QString::fromUtf8("actionStatus_Bar"));
        actionStatus_Bar->setCheckable(true);
        actionStatus_Bar->setChecked(true);
        actionStatus_Bar->setEnabled(true);
        actionRedo = new QAction(MainWindow);
        actionRedo->setObjectName(QString::fromUtf8("actionRedo"));
        QIcon icon10;
        icon10.addFile(QString::fromUtf8(":/icons/res/icons/redo.bmp"), QSize(), QIcon::Normal, QIcon::On);
        actionRedo->setIcon(icon10);
        actionAuto_Indent = new QAction(MainWindow);
        actionAuto_Indent->setObjectName(QString::fromUtf8("actionAuto_Indent"));
        actionAuto_Indent->setCheckable(true);
        actionAuto_Indent->setChecked(true);
        actionWord_Wrap = new QAction(MainWindow);
        actionWord_Wrap->setObjectName(QString::fromUtf8("actionWord_Wrap"));
        actionWord_Wrap->setCheckable(true);
        actionC_Lang = new QAction(MainWindow);
        actionC_Lang->setObjectName(QString::fromUtf8("actionC_Lang"));
        actionC_Lang->setCheckable(true);
        actionCPP_Lang = new QAction(MainWindow);
        actionCPP_Lang->setObjectName(QString::fromUtf8("actionCPP_Lang"));
        actionCPP_Lang->setCheckable(true);
        actionJava_Lang = new QAction(MainWindow);
        actionJava_Lang->setObjectName(QString::fromUtf8("actionJava_Lang"));
        actionJava_Lang->setCheckable(true);
        actionPython_Lang = new QAction(MainWindow);
        actionPython_Lang->setObjectName(QString::fromUtf8("actionPython_Lang"));
        actionPython_Lang->setCheckable(true);
        actionTool_Bar = new QAction(MainWindow);
        actionTool_Bar->setObjectName(QString::fromUtf8("actionTool_Bar"));
        actionTool_Bar->setCheckable(true);
        actionTool_Bar->setChecked(true);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        tabWidget = new TabbedEditor(centralWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(299, 19, 641, 311));
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 22, 261, 331));
        verticalLayout_2 = new QVBoxLayout(layoutWidget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout_2->addWidget(label);

        comboBox = new QComboBox(layoutWidget);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        verticalLayout_2->addWidget(comboBox);

        label_7 = new QLabel(layoutWidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        verticalLayout_2->addWidget(label_7);

        comboBox_4 = new QComboBox(layoutWidget);
        comboBox_4->addItem(QString());
        comboBox_4->addItem(QString());
        comboBox_4->addItem(QString());
        comboBox_4->addItem(QString());
        comboBox_4->setObjectName(QString::fromUtf8("comboBox_4"));

        verticalLayout_2->addWidget(comboBox_4);

        stackedWidget = new QStackedWidget(layoutWidget);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        stackedWidget->setMinimumSize(QSize(160, 0));
        page_3 = new QWidget();
        page_3->setObjectName(QString::fromUtf8("page_3"));
        stackedWidget->addWidget(page_3);
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        label_2 = new QLabel(page);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(9, 9, 231, 17));
        pushButton = new QPushButton(page);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(10, 70, 231, 31));
        lineEdit_9 = new QLineEdit(page);
        lineEdit_9->setObjectName(QString::fromUtf8("lineEdit_9"));
        lineEdit_9->setGeometry(QRect(10, 40, 221, 25));
        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        verticalLayout = new QVBoxLayout(page_2);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label_3 = new QLabel(page_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        verticalLayout->addWidget(label_3);

        lineEdit = new QLineEdit(page_2);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        verticalLayout->addWidget(lineEdit);

        label_4 = new QLabel(page_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        verticalLayout->addWidget(label_4);

        lineEdit_2 = new QLineEdit(page_2);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));

        verticalLayout->addWidget(lineEdit_2);

        label_5 = new QLabel(page_2);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        verticalLayout->addWidget(label_5);

        lineEdit_3 = new QLineEdit(page_2);
        lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));

        verticalLayout->addWidget(lineEdit_3);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        Connect_Button = new QPushButton(page_2);
        Connect_Button->setObjectName(QString::fromUtf8("Connect_Button"));

        horizontalLayout->addWidget(Connect_Button);

        Disconnect_Button = new QPushButton(page_2);
        Disconnect_Button->setObjectName(QString::fromUtf8("Disconnect_Button"));

        horizontalLayout->addWidget(Disconnect_Button);


        verticalLayout->addLayout(horizontalLayout);

        stackedWidget->addWidget(page_2);

        verticalLayout_2->addWidget(stackedWidget);

        stackedWidget_2 = new QStackedWidget(centralWidget);
        stackedWidget_2->setObjectName(QString::fromUtf8("stackedWidget_2"));
        stackedWidget_2->setGeometry(QRect(20, 370, 241, 171));
        page_7 = new QWidget();
        page_7->setObjectName(QString::fromUtf8("page_7"));
        stackedWidget_2->addWidget(page_7);
        page_6 = new QWidget();
        page_6->setObjectName(QString::fromUtf8("page_6"));
        verticalLayout_3 = new QVBoxLayout(page_6);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        label_6 = new QLabel(page_6);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        verticalLayout_3->addWidget(label_6);

        lineEdit_7 = new QLineEdit(page_6);
        lineEdit_7->setObjectName(QString::fromUtf8("lineEdit_7"));

        verticalLayout_3->addWidget(lineEdit_7);

        Load_Button = new QPushButton(page_6);
        Load_Button->setObjectName(QString::fromUtf8("Load_Button"));

        verticalLayout_3->addWidget(Load_Button);

        label_11 = new QLabel(page_6);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        verticalLayout_3->addWidget(label_11);

        lineEdit_8 = new QLineEdit(page_6);
        lineEdit_8->setObjectName(QString::fromUtf8("lineEdit_8"));

        verticalLayout_3->addWidget(lineEdit_8);

        Upload_Button = new QPushButton(page_6);
        Upload_Button->setObjectName(QString::fromUtf8("Upload_Button"));

        verticalLayout_3->addWidget(Upload_Button);

        stackedWidget_2->addWidget(page_6);
        page_8 = new QWidget();
        page_8->setObjectName(QString::fromUtf8("page_8"));
        verticalLayout_4 = new QVBoxLayout(page_8);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        label_8 = new QLabel(page_8);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        verticalLayout_4->addWidget(label_8);

        lineEdit_4 = new QLineEdit(page_8);
        lineEdit_4->setObjectName(QString::fromUtf8("lineEdit_4"));

        verticalLayout_4->addWidget(lineEdit_4);

        label_10 = new QLabel(page_8);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        verticalLayout_4->addWidget(label_10);

        lineEdit_6 = new QLineEdit(page_8);
        lineEdit_6->setObjectName(QString::fromUtf8("lineEdit_6"));

        verticalLayout_4->addWidget(lineEdit_6);

        pushButton_2 = new QPushButton(page_8);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        verticalLayout_4->addWidget(pushButton_2);

        stackedWidget_2->addWidget(page_8);
        page_9 = new QWidget();
        page_9->setObjectName(QString::fromUtf8("page_9"));
        verticalLayout_5 = new QVBoxLayout(page_9);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        label_9 = new QLabel(page_9);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        verticalLayout_5->addWidget(label_9);

        lineEdit_5 = new QLineEdit(page_9);
        lineEdit_5->setObjectName(QString::fromUtf8("lineEdit_5"));

        verticalLayout_5->addWidget(lineEdit_5);

        pushButton_3 = new QPushButton(page_9);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));

        verticalLayout_5->addWidget(pushButton_3);

        stackedWidget_2->addWidget(page_9);
        tabWidget_2 = new QTabWidget(centralWidget);
        tabWidget_2->setObjectName(QString::fromUtf8("tabWidget_2"));
        tabWidget_2->setGeometry(QRect(300, 350, 641, 181));
        tabWidget_2->setTabsClosable(true);
        tabWidget_2->setMovable(true);
        MainWindow->setCentralWidget(centralWidget);
        layoutWidget->raise();
        tabWidget->raise();
        stackedWidget_2->raise();
        tabWidget_2->raise();
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 922, 22));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuEdit = new QMenu(menuBar);
        menuEdit->setObjectName(QString::fromUtf8("menuEdit"));
        menuFormat = new QMenu(menuBar);
        menuFormat->setObjectName(QString::fromUtf8("menuFormat"));
        menuLanguage = new QMenu(menuFormat);
        menuLanguage->setObjectName(QString::fromUtf8("menuLanguage"));
        menuView = new QMenu(menuBar);
        menuView->setObjectName(QString::fromUtf8("menuView"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        statusBar->setEnabled(true);
        MainWindow->setStatusBar(statusBar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);
        toolBar_2 = new QToolBar(MainWindow);
        toolBar_2->setObjectName(QString::fromUtf8("toolBar_2"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar_2);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuEdit->menuAction());
        menuBar->addAction(menuFormat->menuAction());
        menuBar->addAction(menuView->menuAction());
        menuFile->addAction(actionNew);
        menuFile->addAction(actionOpen);
        menuFile->addAction(actionSave);
        menuFile->addAction(actionSave_As);
        menuFile->addSeparator();
        menuFile->addAction(actionPrint);
        menuFile->addSeparator();
        menuFile->addAction(actionExit);
        menuEdit->addAction(actionUndo);
        menuEdit->addAction(actionRedo);
        menuEdit->addSeparator();
        menuEdit->addAction(actionCut);
        menuEdit->addAction(actionCopy);
        menuEdit->addAction(actionPaste);
        menuEdit->addSeparator();
        menuEdit->addAction(actionFind);
        menuEdit->addAction(actionReplace);
        menuEdit->addAction(actionGo_To);
        menuEdit->addSeparator();
        menuEdit->addAction(actionSelect_All);
        menuEdit->addAction(actionTime_Date);
        menuFormat->addAction(actionFont);
        menuFormat->addAction(menuLanguage->menuAction());
        menuFormat->addAction(actionAuto_Indent);
        menuFormat->addAction(actionWord_Wrap);
        menuLanguage->addAction(actionC_Lang);
        menuLanguage->addAction(actionCPP_Lang);
        menuLanguage->addAction(actionJava_Lang);
        menuLanguage->addAction(actionPython_Lang);
        menuView->addAction(actionStatus_Bar);
        menuView->addAction(actionTool_Bar);
        mainToolBar->addAction(actionNew);
        mainToolBar->addAction(actionOpen);
        mainToolBar->addAction(actionSave);
        mainToolBar->addAction(actionSave_As);
        mainToolBar->addAction(actionPrint);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionUndo);
        mainToolBar->addAction(actionRedo);
        mainToolBar->addAction(actionCopy);
        mainToolBar->addAction(actionCut);
        mainToolBar->addAction(actionPaste);
        mainToolBar->addAction(actionFind);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(-1);
        stackedWidget->setCurrentIndex(1);
        stackedWidget_2->setCurrentIndex(3);
        tabWidget_2->setCurrentIndex(-1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        actionNew->setText(QApplication::translate("MainWindow", "New", nullptr));
#ifndef QT_NO_SHORTCUT
        actionNew->setShortcut(QApplication::translate("MainWindow", "Ctrl+N", nullptr));
#endif // QT_NO_SHORTCUT
        actionOpen->setText(QApplication::translate("MainWindow", "Open", nullptr));
#ifndef QT_NO_SHORTCUT
        actionOpen->setShortcut(QApplication::translate("MainWindow", "Ctrl+O", nullptr));
#endif // QT_NO_SHORTCUT
        actionSave->setText(QApplication::translate("MainWindow", "Save", nullptr));
#ifndef QT_NO_SHORTCUT
        actionSave->setShortcut(QApplication::translate("MainWindow", "Ctrl+S", nullptr));
#endif // QT_NO_SHORTCUT
        actionSave_As->setText(QApplication::translate("MainWindow", "Save As", nullptr));
#ifndef QT_NO_SHORTCUT
        actionSave_As->setShortcut(QApplication::translate("MainWindow", "Ctrl+Shift+S", nullptr));
#endif // QT_NO_SHORTCUT
        actionPrint->setText(QApplication::translate("MainWindow", "Print...", nullptr));
#ifndef QT_NO_SHORTCUT
        actionPrint->setShortcut(QApplication::translate("MainWindow", "Ctrl+P", nullptr));
#endif // QT_NO_SHORTCUT
        actionExit->setText(QApplication::translate("MainWindow", "Exit", nullptr));
        actionUndo->setText(QApplication::translate("MainWindow", "Undo", nullptr));
#ifndef QT_NO_SHORTCUT
        actionUndo->setShortcut(QApplication::translate("MainWindow", "Ctrl+Z", nullptr));
#endif // QT_NO_SHORTCUT
        actionCut->setText(QApplication::translate("MainWindow", "Cut", nullptr));
#ifndef QT_NO_SHORTCUT
        actionCut->setShortcut(QApplication::translate("MainWindow", "Ctrl+X", nullptr));
#endif // QT_NO_SHORTCUT
        actionCopy->setText(QApplication::translate("MainWindow", "Copy", nullptr));
#ifndef QT_NO_SHORTCUT
        actionCopy->setShortcut(QApplication::translate("MainWindow", "Ctrl+C", nullptr));
#endif // QT_NO_SHORTCUT
        actionPaste->setText(QApplication::translate("MainWindow", "Paste", nullptr));
#ifndef QT_NO_SHORTCUT
        actionPaste->setShortcut(QApplication::translate("MainWindow", "Ctrl+V", nullptr));
#endif // QT_NO_SHORTCUT
        actionFind->setText(QApplication::translate("MainWindow", "Find...", nullptr));
#ifndef QT_NO_SHORTCUT
        actionFind->setShortcut(QApplication::translate("MainWindow", "Ctrl+F", nullptr));
#endif // QT_NO_SHORTCUT
        actionReplace->setText(QApplication::translate("MainWindow", "Replace...", nullptr));
#ifndef QT_NO_SHORTCUT
        actionReplace->setShortcut(QApplication::translate("MainWindow", "Ctrl+H", nullptr));
#endif // QT_NO_SHORTCUT
        actionGo_To->setText(QApplication::translate("MainWindow", "Go To...", nullptr));
#ifndef QT_NO_SHORTCUT
        actionGo_To->setShortcut(QApplication::translate("MainWindow", "Ctrl+G", nullptr));
#endif // QT_NO_SHORTCUT
        actionSelect_All->setText(QApplication::translate("MainWindow", "Select All", nullptr));
#ifndef QT_NO_SHORTCUT
        actionSelect_All->setShortcut(QApplication::translate("MainWindow", "Ctrl+A", nullptr));
#endif // QT_NO_SHORTCUT
        actionTime_Date->setText(QApplication::translate("MainWindow", "Time/Date", nullptr));
#ifndef QT_NO_SHORTCUT
        actionTime_Date->setShortcut(QApplication::translate("MainWindow", "F5", nullptr));
#endif // QT_NO_SHORTCUT
        actionFont->setText(QApplication::translate("MainWindow", "Font...", nullptr));
        actionStatus_Bar->setText(QApplication::translate("MainWindow", "Status Bar", nullptr));
        actionRedo->setText(QApplication::translate("MainWindow", "Redo", nullptr));
#ifndef QT_NO_SHORTCUT
        actionRedo->setShortcut(QApplication::translate("MainWindow", "Ctrl+Y", nullptr));
#endif // QT_NO_SHORTCUT
        actionAuto_Indent->setText(QApplication::translate("MainWindow", "Auto Indent", nullptr));
        actionWord_Wrap->setText(QApplication::translate("MainWindow", "Word Wrap", nullptr));
        actionC_Lang->setText(QApplication::translate("MainWindow", "C", nullptr));
        actionCPP_Lang->setText(QApplication::translate("MainWindow", "C++", nullptr));
        actionJava_Lang->setText(QApplication::translate("MainWindow", "Java", nullptr));
        actionPython_Lang->setText(QApplication::translate("MainWindow", "Python", nullptr));
        actionTool_Bar->setText(QApplication::translate("MainWindow", "Tool Bar", nullptr));
        label->setText(QApplication::translate("MainWindow", "Machine", nullptr));
        comboBox->setItemText(0, QApplication::translate("MainWindow", "Local", nullptr));
        comboBox->setItemText(1, QApplication::translate("MainWindow", "Remote", nullptr));

        label_7->setText(QApplication::translate("MainWindow", "Mode", nullptr));
        comboBox_4->setItemText(0, QString());
        comboBox_4->setItemText(1, QApplication::translate("MainWindow", "Configure", nullptr));
        comboBox_4->setItemText(2, QApplication::translate("MainWindow", "Download", nullptr));
        comboBox_4->setItemText(3, QApplication::translate("MainWindow", "Upload", nullptr));

        label_2->setText(QApplication::translate("MainWindow", "File Path To edit", nullptr));
        pushButton->setText(QApplication::translate("MainWindow", "Load", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "Hostname", nullptr));
        label_4->setText(QApplication::translate("MainWindow", "username", nullptr));
        label_5->setText(QApplication::translate("MainWindow", "password", nullptr));
        Connect_Button->setText(QApplication::translate("MainWindow", "Connect", nullptr));
        Disconnect_Button->setText(QApplication::translate("MainWindow", "Disconnect", nullptr));
        label_6->setText(QApplication::translate("MainWindow", "Remote File Path to Edit", nullptr));
        Load_Button->setText(QApplication::translate("MainWindow", "Load", nullptr));
        label_11->setText(QApplication::translate("MainWindow", "Remote File Path to Upload File", nullptr));
        Upload_Button->setText(QApplication::translate("MainWindow", "Upload", nullptr));
        label_8->setText(QApplication::translate("MainWindow", "Remote File Path ", nullptr));
        lineEdit_4->setText(QString());
        label_10->setText(QApplication::translate("MainWindow", "Traget File name to save ", nullptr));
        pushButton_2->setText(QApplication::translate("MainWindow", "Download", nullptr));
        label_9->setText(QApplication::translate("MainWindow", "Remote Upload  Path ", nullptr));
        pushButton_3->setText(QApplication::translate("MainWindow", "Upload", nullptr));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", nullptr));
        menuEdit->setTitle(QApplication::translate("MainWindow", "Edit", nullptr));
        menuFormat->setTitle(QApplication::translate("MainWindow", "Format", nullptr));
        menuLanguage->setTitle(QApplication::translate("MainWindow", "Language", nullptr));
        menuView->setTitle(QApplication::translate("MainWindow", "View", nullptr));
        toolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", nullptr));
        toolBar_2->setWindowTitle(QApplication::translate("MainWindow", "toolBar_2", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
