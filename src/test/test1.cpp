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
    GENERATOR(randStr, Generators::StringGen, 1, 2, 5);
    BOUND_GENERATOR(randStr, rangeNumber, Generators::Range, 2);
    BOUND_GENERATOR(rangeNumber, rangeChar, Generators::RangeType<char>, 'a', 'e');
    formatPrint("First Test with generator! EEaarrr baby!! '", getTestName(), "' Generated str: ", randStr);
    print("Generated number: ", rangeNumber);
    print("Generated char: ", rangeChar);
    return true;
}

#include "../profiler.h"

TEST_SIMPLE_S(TestSecondSuite, SecondSuite) {
    GENERATOR(rangeNumber, Generators::Range, 2, 5, 5);
    formatPrint("Test of second Suite! EEaarrr baby!! '", getSuiteName(), "' Start", rangeNumber);
    std::vector<int> vectorByka(5, 15);
    TRACE_VAR(vectorByka);
    TRACE_VAR(rangeNumber);
    return true;
}

#include "../toString.h"
#include <vector>
#include <map>

TEST_SIMPLE(Test_ToString) {
    formatPrint(ToString(
        std::vector<int>(5, 15), " Baby ", true, std::map<std::string, int>{{"zbc", 10}, {"abc", 1}}, 10.45, 0xff
    ));
    return true;
}


TEST_SIMPLE_S(Test_Asserts, FirstSuite) {
    
    return true;
}

#include "../tables/tables.h"

TEST_SIMPLE_N(Test_CLTable, 0) {
    GENERATOR(rangeNumber, Generators::Range, 2, 5, 5);
    tables::Table genTable;
    tables::CLTableView tableCLview(genTable);

    genTable.addCell("Column 1");
    genTable.addCell("Column 2");
    genTable.nextRow();
    genTable.addCell("SubColumn 1");
    genTable.addSubCell("SubColumn 2");
    genTable.addCell("SubColumn 1");
    genTable.addSubCell("SubColumn 2");
    genTable.nextRow();
    genTable.addCell("FirstCell");
    genTable.nextRow(true);
    // CLTableView table1(160);
    // CLTableView table2(CLTableView::TableBorders
        // {2, tables::Border::Default(), tables::Border{'#', '_', '&'}}
    // );
    return true;
}
