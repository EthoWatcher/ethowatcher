#include "test_generate_report.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    test_generate_report w;
    w.show();
    return a.exec();
}
