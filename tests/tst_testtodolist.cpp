#include <QtTest>

// add necessary includes here

class testtodolist : public QObject
{
    Q_OBJECT

public:
    testtodolist();
    ~testtodolist();

private slots:
    void test_case1();

};

testtodolist::testtodolist()
{

}

testtodolist::~testtodolist()
{

}

void testtodolist::test_case1()
{

}

QTEST_APPLESS_MAIN(testtodolist)

#include "tst_testtodolist.moc"
