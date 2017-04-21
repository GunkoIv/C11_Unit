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
    formatPrint("I'm must be first test with name '", getTestName(), "' Start execution!");
    return true;
}