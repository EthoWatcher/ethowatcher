#include <QString>
#include <QtTest>

class Teste_analise_concordanciaTest : public QObject
{
    Q_OBJECT

public:
    Teste_analise_concordanciaTest();

private Q_SLOTS:
    void testCase1();
};

Teste_analise_concordanciaTest::Teste_analise_concordanciaTest()
{
}

void Teste_analise_concordanciaTest::testCase1()
{
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(Teste_analise_concordanciaTest)

#include "tst_teste_analise_concordanciatest.moc"
