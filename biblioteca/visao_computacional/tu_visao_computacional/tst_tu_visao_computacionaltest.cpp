#include <QString>
#include <QtTest>

#include "visao_computacional.h"
#include <QDebug>
class Tu_visao_computacionalTest : public QObject
{
    Q_OBJECT

public:
    Tu_visao_computacionalTest();

private Q_SLOTS:
    void testCase1();
    void testCase2();
};

Tu_visao_computacionalTest::Tu_visao_computacionalTest()
{
}

void Tu_visao_computacionalTest::testCase1()
{
    Visao_computacional vis;
    int a = vis.Soma(10,20);
    qDebug() << a;
    QVERIFY2(true, "Failure");
}

void Tu_visao_computacionalTest::testCase2()
{
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(Tu_visao_computacionalTest)

#include "tst_tu_visao_computacionaltest.moc"
