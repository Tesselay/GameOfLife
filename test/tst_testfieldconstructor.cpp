#include <QtTest>
#include <QList>
#include "../playfield.h"
#include "../gamelogic.h"

class TestFieldConstructor : public QObject
{
    Q_OBJECT

public:
    TestFieldConstructor();
    ~TestFieldConstructor();

private:
    QList<QStringList> field_to_test;
    Playfield play_field;
    GameLogic game_logic;

private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_size();
    void test_content();

};

TestFieldConstructor::TestFieldConstructor()
{
}

TestFieldConstructor::~TestFieldConstructor()
{
}

void TestFieldConstructor::initTestCase()
{
    qDebug("Init");
    field_to_test = play_field.field_constructor(game_logic.field_size, game_logic.dead_cell);
}

void TestFieldConstructor::cleanupTestCase()
{
    qDebug("CleanUP");
}

void TestFieldConstructor::test_size()
{
    QTRY_COMPARE(field_to_test.size(), 50);
    for (int i {0}; i < field_to_test.size(); i++) {
        QTRY_COMPARE(field_to_test[i].size(), 50);
    }
}

void TestFieldConstructor::test_content()
{
    for ( int i {0}; i < field_to_test.size(); i++) {
        for ( int j {0}; j < field_to_test[i].size(); j++) {
            QTRY_COMPARE(field_to_test[i].at(j), "   ");
        }
    }
}

QTEST_APPLESS_MAIN(TestFieldConstructor)

#include "tst_testfieldconstructor.moc"
