#ifndef GUN_TEST_ITEST_SUITE_H_
#define GUN_TEST_ITEST_SUITE_H_

#include "Structures.h"
// #include "ISuite.h"
#include "ITest.h"
#include "SuiteKeeper.h"

namespace gun { namespace test {

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

} } //namespace test and gun

#endif //GUN_TEST_ITEST_SUITE_H_
