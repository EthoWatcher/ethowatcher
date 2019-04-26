/********************************************************************************
** Form generated from reading UI file 'telacego.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TELACEGO_H
#define UI_TELACEGO_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_telaCego
{
public:
    QGroupBox *groupBox;
    QPushButton *pbAddListaVideo;
    QGroupBox *groupBox_2;
    QPushButton *pbAbrirPasta;
    QGroupBox *groupBox_3;
    QTextEdit *textEdit_3;
    QGroupBox *groupBox_4;
    QStackedWidget *staWidPrin;
    QWidget *page_4;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox_8;
    QVBoxLayout *verticalLayout_4;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents_2;
    QVBoxLayout *verticalLayout_5;
    QTableWidget *tabWidVideoList;
    QWidget *page_5;
    QVBoxLayout *verticalLayout_3;
    QGroupBox *groupBox_9;
    QVBoxLayout *verticalLayout_2;
    QScrollArea *saProgress;
    QWidget *scrollAreaWidgetContents;
    QGroupBox *groupBox_5;
    QLineEdit *leNomePadr;
    QGroupBox *groupBox_6;
    QPushButton *pbBliding;
    QGroupBox *groupBox_7;
    QPushButton *pbSetUserKey;
    QGroupBox *groupBox_10;
    QLabel *label_26;
    QComboBox *comboBoX;

    void setupUi(QWidget *telaCego)
    {
        if (telaCego->objectName().isEmpty())
            telaCego->setObjectName(QStringLiteral("telaCego"));
        telaCego->resize(741, 633);
        groupBox = new QGroupBox(telaCego);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(30, 150, 141, 81));
        pbAddListaVideo = new QPushButton(groupBox);
        pbAddListaVideo->setObjectName(QStringLiteral("pbAddListaVideo"));
        pbAddListaVideo->setGeometry(QRect(20, 30, 101, 23));
        groupBox_2 = new QGroupBox(telaCego);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(180, 150, 151, 80));
        pbAbrirPasta = new QPushButton(groupBox_2);
        pbAbrirPasta->setObjectName(QStringLiteral("pbAbrirPasta"));
        pbAbrirPasta->setGeometry(QRect(10, 30, 131, 23));
        groupBox_3 = new QGroupBox(telaCego);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(20, 460, 351, 131));
        textEdit_3 = new QTextEdit(groupBox_3);
        textEdit_3->setObjectName(QStringLiteral("textEdit_3"));
        textEdit_3->setGeometry(QRect(20, 30, 311, 71));
        groupBox_4 = new QGroupBox(telaCego);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setGeometry(QRect(430, 460, 261, 121));
        staWidPrin = new QStackedWidget(telaCego);
        staWidPrin->setObjectName(QStringLiteral("staWidPrin"));
        staWidPrin->setGeometry(QRect(350, 150, 381, 261));
        page_4 = new QWidget();
        page_4->setObjectName(QStringLiteral("page_4"));
        verticalLayout = new QVBoxLayout(page_4);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        groupBox_8 = new QGroupBox(page_4);
        groupBox_8->setObjectName(QStringLiteral("groupBox_8"));
        verticalLayout_4 = new QVBoxLayout(groupBox_8);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        scrollArea = new QScrollArea(groupBox_8);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName(QStringLiteral("scrollAreaWidgetContents_2"));
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 79, 79));
        verticalLayout_5 = new QVBoxLayout(scrollAreaWidgetContents_2);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        tabWidVideoList = new QTableWidget(scrollAreaWidgetContents_2);
        tabWidVideoList->setObjectName(QStringLiteral("tabWidVideoList"));
        tabWidVideoList->setRowCount(0);
        tabWidVideoList->setColumnCount(0);
        tabWidVideoList->horizontalHeader()->setStretchLastSection(true);
        tabWidVideoList->verticalHeader()->setStretchLastSection(false);

        verticalLayout_5->addWidget(tabWidVideoList);

        scrollArea->setWidget(scrollAreaWidgetContents_2);

        verticalLayout_4->addWidget(scrollArea);


        verticalLayout->addWidget(groupBox_8);

        staWidPrin->addWidget(page_4);
        page_5 = new QWidget();
        page_5->setObjectName(QStringLiteral("page_5"));
        verticalLayout_3 = new QVBoxLayout(page_5);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        groupBox_9 = new QGroupBox(page_5);
        groupBox_9->setObjectName(QStringLiteral("groupBox_9"));
        verticalLayout_2 = new QVBoxLayout(groupBox_9);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        saProgress = new QScrollArea(groupBox_9);
        saProgress->setObjectName(QStringLiteral("saProgress"));
        saProgress->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 337, 204));
        saProgress->setWidget(scrollAreaWidgetContents);

        verticalLayout_2->addWidget(saProgress);


        verticalLayout_3->addWidget(groupBox_9);

        staWidPrin->addWidget(page_5);
        groupBox_5 = new QGroupBox(telaCego);
        groupBox_5->setObjectName(QStringLiteral("groupBox_5"));
        groupBox_5->setGeometry(QRect(20, 240, 151, 81));
        leNomePadr = new QLineEdit(groupBox_5);
        leNomePadr->setObjectName(QStringLiteral("leNomePadr"));
        leNomePadr->setGeometry(QRect(20, 30, 113, 20));
        groupBox_6 = new QGroupBox(telaCego);
        groupBox_6->setObjectName(QStringLiteral("groupBox_6"));
        groupBox_6->setGeometry(QRect(190, 340, 151, 71));
        pbBliding = new QPushButton(groupBox_6);
        pbBliding->setObjectName(QStringLiteral("pbBliding"));
        pbBliding->setGeometry(QRect(20, 30, 101, 23));
        groupBox_7 = new QGroupBox(telaCego);
        groupBox_7->setObjectName(QStringLiteral("groupBox_7"));
        groupBox_7->setGeometry(QRect(180, 240, 151, 81));
        pbSetUserKey = new QPushButton(groupBox_7);
        pbSetUserKey->setObjectName(QStringLiteral("pbSetUserKey"));
        pbSetUserKey->setGeometry(QRect(30, 30, 75, 23));
        groupBox_10 = new QGroupBox(telaCego);
        groupBox_10->setObjectName(QStringLiteral("groupBox_10"));
        groupBox_10->setGeometry(QRect(20, 340, 151, 81));
        label_26 = new QLabel(groupBox_10);
        label_26->setObjectName(QStringLiteral("label_26"));
        label_26->setGeometry(QRect(10, 20, 51, 16));
        comboBoX = new QComboBox(groupBox_10);
        comboBoX->setObjectName(QStringLiteral("comboBoX"));
        comboBoX->setGeometry(QRect(10, 42, 131, 20));

        retranslateUi(telaCego);

        staWidPrin->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(telaCego);
    } // setupUi

    void retranslateUi(QWidget *telaCego)
    {
        telaCego->setWindowTitle(QApplication::translate("telaCego", "Form", 0));
        groupBox->setTitle(QApplication::translate("telaCego", "Step 1.01", 0));
        pbAddListaVideo->setText(QApplication::translate("telaCego", "Open List Video", 0));
        groupBox_2->setTitle(QApplication::translate("telaCego", "Step 1.02", 0));
        pbAbrirPasta->setText(QApplication::translate("telaCego", "Set Destination Folder", 0));
        groupBox_3->setTitle(QApplication::translate("telaCego", "Tutor", 0));
        groupBox_4->setTitle(QApplication::translate("telaCego", "To-do-list", 0));
        groupBox_8->setTitle(QApplication::translate("telaCego", "Video List", 0));
        groupBox_9->setTitle(QApplication::translate("telaCego", "Progress Blind", 0));
        groupBox_5->setTitle(QApplication::translate("telaCego", "Step 1.03", 0));
        leNomePadr->setText(QApplication::translate("telaCego", "blind", 0));
        groupBox_6->setTitle(QApplication::translate("telaCego", "step 1.05", 0));
        pbBliding->setText(QApplication::translate("telaCego", "\"Blinding\"", 0));
        groupBox_7->setTitle(QApplication::translate("telaCego", "Step 1.04", 0));
        pbSetUserKey->setText(QApplication::translate("telaCego", "Set User Key", 0));
        groupBox_10->setTitle(QApplication::translate("telaCego", "Step 1.05", 0));
        label_26->setText(QApplication::translate("telaCego", "Codec", 0));
        comboBoX->clear();
        comboBoX->insertItems(0, QStringList()
         << QApplication::translate("telaCego", "Microsoft RLE", 0)
         << QApplication::translate("telaCego", "Microsoft Video1", 0)
         << QApplication::translate("telaCego", "Intel IYUV codec", 0)
         << QApplication::translate("telaCego", "Cinepack Codec by radius", 0)
         << QApplication::translate("telaCego", "Lagarith Lossles Codec", 0)
         << QApplication::translate("telaCego", "H264", 0)
         << QApplication::translate("telaCego", "XVid", 0)
         << QApplication::translate("telaCego", "ffdshow Video Codec", 0)
         << QApplication::translate("telaCego", "H264", 0)
        );
    } // retranslateUi

};

namespace Ui {
    class telaCego: public Ui_telaCego {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TELACEGO_H
