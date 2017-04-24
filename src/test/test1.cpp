// Кодировка utf-8.
#include "executor.h"
#include "Macroses.h"

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

SUITE(MyFirstTtrulySuite)
    void setup() {
        print("Hi Man! It's ", getSuiteName(), " Statrts ^)");
    }
    void teardown() {
        print(getSuiteName(), " Closing :(");
    }
public:
    const int someInt = 1;
};

TEST_SIMPLE_S(ZImpleSuiteTest, MyFirstTtrulySuite) {
    formatPrint("Last Test with suite! '", getTestName(), "' Start execution!", suite->someInt);
    return true;
}

TEST_SIMPLE_S_N(MyFirstSoiteNumberTest, MyFirstTtrulySuite, 0) {
    formatPrint("First test with suite! '", getTestName(), "' Start execution!", suite->someInt);
    return true;
}

TEST_SIMPLE_S(ATest, MyFirstTtrulySuite) {
    formatPrint("Second test with suite! '", getTestName(), "' Start execution!");
    return true;
}

TEST_SIMPLE_S(MyTest, MyFirstTtrulySuite) {
    formatPrint("Thrid test with suite! '", getTestName(), "' Start execution!");
    return true;
}
