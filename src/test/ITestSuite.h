// Кодировка utf-8.
#ifndef TESTS_ITEST_SUITE_H_
#define TESTS_ITEST_SUITE_H_

#include "Structures.h"
// #include "ISuite.h"
#include "ITest.h"
#include "SuiteKeeper.h"

namespace Cpp11_unit {

    template<typename TheSuite>
    class ITestSuite : public ITest {
    public:
        TheSuite* suite;

        ITestSuite(std::string &&name, SuiteInfo &&suiteInfo)
            : ITest(std::move(name), std::move(suiteInfo))
        {}

        ITestSuite(std::string &&name, SuiteInfo &&suiteInfo, unsigned int orderNumber)
            : ITest(std::move(name), std::move(suiteInfo), orderNumber)
        {}

        ITestSuite(ITestSuite &&) = default;

        virtual ~ITestSuite() = default;

        TestResult virtual execute() override {
            suite = TS_GEN_GET_SUITE(TheSuite, getSuiteName());
            return std::move(ITest::execute());
        }
    };

} //namespace Cpp11_unit

#endif //TESTS_ITEST_SUITE_H_
