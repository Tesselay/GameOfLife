#include <QtTest>

// add necessary includes here

class TestFieldPrinter : public QObject
{
    Q_OBJECT

public:
    TestFieldPrinter();
    ~TestFieldPrinter();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_case1();

};

TestFieldPrinter::TestFieldPrinter()
{

}

TestFieldPrinter::~TestFieldPrinter()
{

}

void TestFieldPrinter::initTestCase()
{
    qDebug("Init");
}

void TestFieldPrinter::cleanupTestCase()
{
    qDebug("CleanUP");
}

void TestFieldPrinter::test_case1()
{
    qDebug("TestCase1");
}

QTEST_GUILESS_MAIN(TestFieldPrinter)

#include "tst_testfieldprinter.moc"
