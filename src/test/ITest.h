// Кодировка utf-8.
#ifndef TESTS_ITEST_H_
#define TESTS_ITEST_H_

#include "TestsKeeper.h"
#include "Structures.h"
#include "IPrinter.h"
#include "IFixture.h"
#include "IGenerator.h"
#include "Assert.h"

namespace Cpp11_unit {

    class LessTestOrder;

    class ITest : public GeneratorsKeeper {
    friend LessTestOrder;
    public:

        ITest(std::string &&name)
            : m_name(std::move(name))
        {}

        ITest(std::string &&name, unsigned int orderNumber)
            : m_name(std::move(name))
            , m_order_num(orderNumber)
        {
            TRACE_PRINT("What's UP?");
        }

        ITest(std::string &&name, SuiteInfo &&suite)
            : m_name(std::move(name))
            , m_suiteInfo(std::move(suite))
        {}

        ITest(std::string &&name, SuiteInfo &&suite, unsigned int orderNumber)
            : m_name(std::move(name))
            , m_suiteInfo(std::move(suite))
            , m_order_num(orderNumber)
        {}

        ITest(ITest &&) = default;
        virtual ~ITest() = default;

        template<typename ...Args>
        void print(Args&& ...args) {
            m_printer->print(std::forward<Args>(args)...);
        }

        template<typename ...Args>
        void formatPrint(const std::string &str, Args&& ...args) {
            m_printer->formatPrint(str, std::forward<Args>(args)...);
        }

        TestResult virtual execute() {
            try {
                TRACE_PRINT("Hi there: ", getSuiteName(), ":", 
                    CLPrint<CLColor::YELLOW>(getTestName()), ":", m_order_num, "!");
                execute_body();
                TRACE_PRINT("After '",getTestName(), "' body");
            } catch(TestResult &assertError) {
                return std::move(assertError);
            }
            // TODO Expect
            return std::move(TestResult::Good());
        }

        const std::string & getTestName() {
            return m_name;
        }

        const std::string & getSuiteName() {
            return m_suiteInfo.name;
        }
        
    protected: 

        void registerTests() {
            TRACE_PRINT("S Register");
            TS_GEN_ENSURE_TESTS_STORE_CREATED;
            TS_GEN_ADD_TEST(this);
        }

        void virtual execute_body() = 0;

    private:
        const std::string m_name;
        const SuiteInfo m_suiteInfo;
        const unsigned int m_order_num = Default::defaultOrderNumber;

        Unique<IPrinter> m_printer;
        Container<IFixture> m_fixtures {};
    };

} //namespace Cpp11_unit

#endif //TESTS_ITEST_H_
