#include "tst_testfieldconstructor.h"

TestFieldConstructor::TestFieldConstructor()
{
}

TestFieldConstructor::~TestFieldConstructor()
{
}

void TestFieldConstructor::initTestCase()
{
    field_to_test = play_field.field_constructor(40, " _ ");
}

void TestFieldConstructor::cleanupTestCase()
{
}

void TestFieldConstructor::test_size()
{
    QTRY_COMPARE(field_to_test.size(), 40);
    for (int i {0}; i < field_to_test.size(); i++) {
        QTRY_COMPARE(field_to_test[i].size(), 40);
    }
}

void TestFieldConstructor::test_content()
{
    for ( int i {0}; i < field_to_test.size(); i++) {
        for ( int j {0}; j < field_to_test[i].size(); j++) {
            QTRY_COMPARE(field_to_test[i].at(j), " _ ");
        }
    }
}

#include "tst_testfieldconstructor.moc"
