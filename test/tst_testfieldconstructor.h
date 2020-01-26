#ifndef TST_TESTFIELDCONSTRUCTOR_H
#define TST_TESTFIELDCONSTRUCTOR_H
#include <QtTest/QtTest>
#include <QList>
#include "../playfield.h"

class TestFieldConstructor : public QObject
{
    Q_OBJECT
public:
    TestFieldConstructor();
    ~TestFieldConstructor();

private:
    QList<QStringList> field_to_test;
    Playfield play_field;

private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_size();
    void test_content();

};

#endif // TST_TESTFIELDCONSTRUCTOR_H
