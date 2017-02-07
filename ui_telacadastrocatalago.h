/********************************************************************************
** Form generated from reading UI file 'telacadastrocatalago.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TELACADASTROCATALAGO_H
#define UI_TELACADASTROCATALAGO_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_telaCadastroCatalago
{
public:
    QGroupBox *groupBox;
    QLineEdit *leCategoria;
    QLabel *label;
    QLineEdit *leAtalho;
    QLabel *label_2;
    QLabel *label_3;
    QTextEdit *textDscElem;
    QPushButton *pbAddCategoria;
    QGroupBox *groupBox_2;
    QTableWidget *tabDadCat;
    QPushButton *pbClearItem;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout;
    QTextEdit *textEdit;
    QGroupBox *groupBox_4;
    QVBoxLayout *verticalLayout_2;
    QPushButton *pbCadastroCatalago;
    QLabel *label_4;

    void setupUi(QWidget *telaCadastroCatalago)
    {
        if (telaCadastroCatalago->objectName().isEmpty())
            telaCadastroCatalago->setObjectName(QStringLiteral("telaCadastroCatalago"));
        telaCadastroCatalago->resize(562, 538);
        groupBox = new QGroupBox(telaCadastroCatalago);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(20, 70, 241, 331));
        leCategoria = new QLineEdit(groupBox);
        leCategoria->setObjectName(QStringLiteral("leCategoria"));
        leCategoria->setGeometry(QRect(10, 50, 151, 20));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 30, 171, 16));
        leAtalho = new QLineEdit(groupBox);
        leAtalho->setObjectName(QStringLiteral("leAtalho"));
        leAtalho->setGeometry(QRect(10, 100, 113, 20));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 80, 171, 16));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(20, 140, 131, 16));
        textDscElem = new QTextEdit(groupBox);
        textDscElem->setObjectName(QStringLiteral("textDscElem"));
        textDscElem->setGeometry(QRect(10, 180, 221, 91));
        pbAddCategoria = new QPushButton(groupBox);
        pbAddCategoria->setObjectName(QStringLiteral("pbAddCategoria"));
        pbAddCategoria->setGeometry(QRect(20, 280, 111, 23));
        groupBox_2 = new QGroupBox(telaCadastroCatalago);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(280, 70, 241, 271));
        tabDadCat = new QTableWidget(groupBox_2);
        if (tabDadCat->columnCount() < 2)
            tabDadCat->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tabDadCat->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tabDadCat->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tabDadCat->setObjectName(QStringLiteral("tabDadCat"));
        tabDadCat->setGeometry(QRect(30, 30, 161, 181));
        QFont font;
        font.setBold(false);
        font.setWeight(50);
        tabDadCat->setFont(font);
        tabDadCat->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tabDadCat->setSelectionMode(QAbstractItemView::SingleSelection);
        tabDadCat->setSelectionBehavior(QAbstractItemView::SelectRows);
        tabDadCat->setGridStyle(Qt::SolidLine);
        tabDadCat->setRowCount(0);
        tabDadCat->setColumnCount(2);
        tabDadCat->horizontalHeader()->setDefaultSectionSize(79);
        tabDadCat->horizontalHeader()->setMinimumSectionSize(79);
        tabDadCat->verticalHeader()->setVisible(false);
        tabDadCat->verticalHeader()->setDefaultSectionSize(20);
        tabDadCat->verticalHeader()->setMinimumSectionSize(19);
        pbClearItem = new QPushButton(groupBox_2);
        pbClearItem->setObjectName(QStringLiteral("pbClearItem"));
        pbClearItem->setGeometry(QRect(50, 220, 123, 23));
        groupBox_3 = new QGroupBox(telaCadastroCatalago);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(10, 420, 531, 101));
        verticalLayout = new QVBoxLayout(groupBox_3);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        textEdit = new QTextEdit(groupBox_3);
        textEdit->setObjectName(QStringLiteral("textEdit"));

        verticalLayout->addWidget(textEdit);

        groupBox_4 = new QGroupBox(telaCadastroCatalago);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setGeometry(QRect(280, 340, 241, 61));
        verticalLayout_2 = new QVBoxLayout(groupBox_4);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        pbCadastroCatalago = new QPushButton(groupBox_4);
        pbCadastroCatalago->setObjectName(QStringLiteral("pbCadastroCatalago"));

        verticalLayout_2->addWidget(pbCadastroCatalago);

        label_4 = new QLabel(telaCadastroCatalago);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(20, 10, 501, 51));
        label_4->setPixmap(QPixmap(QString::fromUtf8(":/recursos/cabecalho4.jpg")));
        label_4->setScaledContents(true);

        retranslateUi(telaCadastroCatalago);

        QMetaObject::connectSlotsByName(telaCadastroCatalago);
    } // setupUi

    void retranslateUi(QWidget *telaCadastroCatalago)
    {
        telaCadastroCatalago->setWindowTitle(QApplication::translate("telaCadastroCatalago", "Register behavioral catalog", 0));
        groupBox->setTitle(QApplication::translate("telaCadastroCatalago", "Insert behavioral category", 0));
        leCategoria->setText(QString());
        label->setText(QApplication::translate("telaCadastroCatalago", "Name", 0));
        leAtalho->setText(QString());
        label_2->setText(QApplication::translate("telaCadastroCatalago", "Code", 0));
        label_3->setText(QApplication::translate("telaCadastroCatalago", "Description", 0));
        textDscElem->setHtml(QApplication::translate("telaCadastroCatalago", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", 0));
        pbAddCategoria->setText(QApplication::translate("telaCadastroCatalago", "Add to catalog", 0));
        groupBox_2->setTitle(QApplication::translate("telaCadastroCatalago", "Behavioral catalog units", 0));
        QTableWidgetItem *___qtablewidgetitem = tabDadCat->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("telaCadastroCatalago", "Category", 0));
        QTableWidgetItem *___qtablewidgetitem1 = tabDadCat->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("telaCadastroCatalago", "Code", 0));
        pbClearItem->setText(QApplication::translate("telaCadastroCatalago", "Delete selected item", 0));
        groupBox_3->setTitle(QApplication::translate("telaCadastroCatalago", "Tutor", 0));
        textEdit->setHtml(QApplication::translate("telaCadastroCatalago", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Insert here ONLY the behavioral categories/units you will use in your experiments. When you finish inputting the units, press <span style=\" font-weight:600;\">Save / Register catalog </span>button the identification will be required in other steps os this session of analysis</p></body></html>", 0));
        groupBox_4->setTitle(QString());
        pbCadastroCatalago->setText(QApplication::translate("telaCadastroCatalago", "Save / Register catalog", 0));
        label_4->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class telaCadastroCatalago: public Ui_telaCadastroCatalago {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TELACADASTROCATALAGO_H
