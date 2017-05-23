// Кодировка utf-8.
#include "executor.h"
#include "Macroses.h"
#include "Generators.h"

TEST_SIMPLE(UserSimpleTest1) {
    formatPrint("Test with name '", getTestName(), "' Start execution!");
    return true;
}

TEST_SIMPLE_N(UserSimpleTest2,  2) {
    formatPrint("LALALa! ", 2+2, " Test with name '", getTestName(), "' Start execution!");
    return true;
}

TEST_SIMPLE_N(UserSimpleTest5,  2) {
    formatPrint("LALALa! ", 5*2, " Test with name '", getTestName(), "' Start execution!");
    return true;
}

TEST_SIMPLE_N(UserFitstSimple_test, 0) {
    formatPrint("I must be first test with name '", getTestName(), "' Start execution!");
    return true;
}

SUITE(SecondSuite)
    void setup() {
        print("Hi Man! It's ", getSuiteName(), " Statrts ^)");
    }
    void teardown() {
        print(getSuiteName(), " Closing :(");
    }
public:
    const int someInt = 1;
SUITE_END

SUITE_N(FirstSuite, 1)
    void setup() {
        print("Hi Man! It's ", getSuiteName(), " Statrts ^)");
    }
    void teardown() {
        print(getSuiteName(), " Closing :(");
    }
public:
    const int someInt = 1;
SUITE_END

TEST_SIMPLE_S(ZImpleSuiteTest, FirstSuite) {
    formatPrint("Last Test with suite! '", getTestName(), "' Start execution!", suite->someInt);
    return true;
}

TEST_SIMPLE_S_N(MyFirstSoiteNumberTest, FirstSuite, 0) {
    formatPrint("First test with suite! '", getTestName(), "' Start execution!", suite->someInt);
    return true;
}

TEST_SIMPLE_S(ATest, FirstSuite) {
    formatPrint("Second test with suite! '", getTestName(), "' Start execution!");
    return true;
}

TEST_SIMPLE_S(MyTest, FirstSuite) {
    formatPrint("Thrid test with suite! '", getTestName(), "' Start execution!");
    return true;
}

TEST_SIMPLE_S(TestGen1, FirstSuite) {
    GENERATOR(randStr, Generators::StringGen, -1, 2, 5);
    BOUND_GENERATOR(randStr, rangeNumber, Generators::Range, 2);
    BOUND_GENERATOR(rangeNumber, rangeChar, Generators::RangeType<char>, 'a', 'e');
    formatPrint("First Test with generator! EEaarrr baby!! '", getTestName(), "' Generated str: ", randStr);
    print("Generated number: ", rangeNumber);
    print("Generated char: ", rangeChar);
    return true;
}

TEST_SIMPLE_S(TestSecondSuite, SecondSuite) {
    GENERATOR(rangeNumber, Generators::Range, 2, 5, 5);
    formatPrint("Test of second Suite! EEaarrr baby!! '", getSuiteName(), "' Start", rangeNumber);
    return true;
}

class CLTableView;

class ITableForView {
public:


protected:
    ITableForView() = default;


private:
// friend CLTableView;
};

class Table : private ITableForView {
public:

    Table() = default;

    void addCell(std::string &&str);
    void addCell(const std::string &str);
    // if makeFit == true then: make current row fir with prev row cell count
    void addNewRow(bool makeFit = false);
};


void Table::addCell(std::string &&str) {

}

void Table::addCell(const std::string &str) {

}

void Table::addNewRow(bool makeFit) {

}

class CLTableView {
public:
    struct Border {
        char horizontal;
        char vertical;
        char cross;

        static constexpr Border Default() {
            return {'|', '-', '-'};
        }
    };

    struct TableBorders {
        unsigned int spaceToBorder;
        Border outer;    
        Border inner;    
    };

    // CLTableView(TableBorders borders, unsigned int maxCharWidth = 80);
    // CLTableView(unsigned int maxCharWidth = 80);
    CLTableView(const Table &table);

    void printTo(std::ostream &cout);

private:
    const ITableForView & m_table;
    const TableBorders m_borders;
};

CLTableView::CLTableView(const Table &table)
    : m_table(table) 
    , m_borders{0, Border::Default(), Border::Default()}
{

}
// CLTableView::CLTableView(TableBorders borders, unsigned int maxCharWidth)
//     : m_borders(borders)
//     // ,
// {

// }

// CLTableView::CLTableView(unsigned int maxCharWidth)
//     : m_borders{0, Border::Default(), Border::Default()}
//     // ,
// {

// }

void CLTableView::printTo(std::ostream &cout) {

}

TEST_SIMPLE_N(Test_CLTable, 0) {
    GENERATOR(rangeNumber, Generators::Range, 2, 5, 5);
    Table genTable;
    CLTableView table0(genTable);
    // CLTableView table1(160);
    // CLTableView table2(CLTableView::TableBorders
        {2, CLTableView::Border::Default(), CLTableView::Border{'#', '_', '&'}}
    );
    return true;
}
