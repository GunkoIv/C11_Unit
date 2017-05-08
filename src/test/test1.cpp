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
    GENERATOR(randStr, Generators::StringGen, 3, 2, 5);
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