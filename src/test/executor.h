// Кодировка utf-8.
#ifndef TESTS_EXECUTOR_H_
#define TESTS_EXECUTOR_H_

#include <iostream>
#include "ITest.h"

#define TS_GEN Cpp11_unit::GeneralTests<Cpp11_unit::Mock>

#define TESTS_START() TS_GEN::run()

namespace Cpp11_unit {

        struct Mock {};

        struct LessTestOrder {
            bool operator() (const ITest *const test1, const ITest *const test2) {
                if (test1->m_suite == nullptr && test2->m_suite != nullptr) {
                    return true;
                } else if (test1->m_suite != nullptr && test2->m_suite == nullptr) {
                    return false;
                } 
                return 
                    (test1->m_suite != nullptr && 
                        (test1->m_suite->m_order_num < test2->m_suite->m_order_num ||
                            test1->m_suite->m_name < test2->m_suite->m_name
                        )
                    ) ||
                    test1->m_order_num < test2->m_order_num || 
                    (test1->m_order_num == test2->m_order_num && 
                        test1->m_name < test2->m_name
                    )
                ;
            }
        };

        using OrderedTests = std::set<ITest *, LessTestOrder>;

        template<typename Mock>
        class GeneralTests {
        public:

            static void run() {
                std::cout << "GLOBAL_tests_ptr.size() = " << GLOBAL_tests_ptr.size() << std::endl;
                for(auto &test : GLOBAL_tests_ptr) {
                    test->exucute();
                }
            }

            static void addTest(ITest *test) {
                if (test != nullptr) {
                    GLOBAL_tests_ptr.insert  (test);
                }
            }

            static OrderedTests GLOBAL_tests_ptr;
        };        

        template <typename Mock>
        OrderedTests GeneralTests<Mock>::GLOBAL_tests_ptr = OrderedTests();

} //namespace Cpp11_unit

#endif //TESTS_EXECUTOR_H_
