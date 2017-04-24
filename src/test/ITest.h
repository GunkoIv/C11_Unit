// Кодировка utf-8.
#ifndef TESTS_ITEST_H_
#define TESTS_ITEST_H_

#include "Structures.h"
#include "ISuite.h"
#include "IPrinter.h"
#include "IFixture.h"

namespace Cpp11_unit {

        class IGenerator {};
        class LessTestOrder;

        class ITest {
        friend LessTestOrder;
        public:

            ITest(std::string &&name)
                : m_name(std::move(name))
            {}

            ITest(std::string &&name, unsigned int orderNumber)
                : m_name(std::move(name))
                , m_order_num(orderNumber)
            {}

            ITest(std::string &&name, SuiteInfo &&suite)
                : m_name(std::move(name))
                , m_suite(std::move(suite))
            {}

            ITest(std::string &&name, SuiteInfo &&suite, unsigned int orderNumber)
                : m_name(std::move(name))
                , m_order_num(orderNumber)
                , m_suite(std::move(suite))
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

            bool virtual exucute() = 0;
        
        protected: 

            const std::string & getTestName() {
                return m_name;
            }

            const std::string & getSuiteName() {
                return m_suite.m_name;
            }

        private:
            const std::string m_name;
            const unsigned int m_order_num = Default::defaultOrderNumber;
            SuiteInfo m_suite;

            Unique<IPrinter> m_printer;
            Container<IGenerator> m_generators{};
            Container<IFixture> m_fixtures {};
        };

} //namespace Cpp11_unit

#endif //TESTS_ITEST_H_
