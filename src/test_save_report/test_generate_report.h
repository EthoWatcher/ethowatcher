#ifndef TEST_GENERATE_REPORT_H
#define TEST_GENERATE_REPORT_H

#include <QMainWindow>
#include <QFile>
#include <QTemporaryFile>
#include <QProcess>
#include <QFileDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class test_generate_report; }
QT_END_NAMESPACE

class test_generate_report : public QMainWindow
{
    Q_OBJECT

public:
    test_generate_report(QWidget *parent = nullptr);
    ~test_generate_report();

private slots:
    void on_pushButton_clicked();

private:
    Ui::test_generate_report *ui;
};
#endif // TEST_GENERATE_REPORT_H
