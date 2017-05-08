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
                if (test1->m_suite.m_order_num < test2->m_suite.m_order_num) {
                    return true;
                } else if (test1->m_suite.m_order_num > test2->m_suite.m_order_num) {
                    return false;
                }
                if (test1->m_suite.m_name < test2->m_suite.m_name) {
                    return true;
                } else if (test1->m_suite.m_name > test2->m_suite.m_name) {
                    return false;
                }
                // }
                if (test1->m_order_num < test2->m_order_num) {
                    return true;
                } else if (test1->m_order_num > test2->m_order_num) {
                    return false;
                }
                if (test1->m_name < test2->m_name) {
                    return true;
                } else if (test1->m_name > test2->m_name) {
                    return false;
                }
                throw std::logic_error("Something went wrong inside LessTestOrder");
            }
        };

        using OrderedTests = std::set<ITest *, LessTestOrder>;

        template<typename Mock>
        class GeneralTests {
        public:

            static void run() {
                std::cout << "GLOBAL_tests_ptr.size() = " << GLOBAL_tests_ptr.size() << std::endl;
                for(auto &test : GLOBAL_tests_ptr) {
                    do {
                        test->exucute();
                    } while (test->switchGenerator());
                }
                if (GLOBAL_suite != nullptr) {
                    GLOBAL_suite.reset();
                }
            }

            static void addTest(ITest *test) {
                if (test != nullptr) {
                    GLOBAL_tests_ptr.insert(test);
                }
            }

            template<typename Suite>
            static Suite * getSuite(const std::string &suiteName) {
                // std::cout << "See to new suite" << std::endl;
                if (suiteName != GLOBAL_last_suite_name) {
                    std::cout << "teardown old and create new suite " << std::endl;
                    GLOBAL_suite.reset();
                    GLOBAL_suite.reset(new SetupWrapper<Suite>());
                    GLOBAL_last_suite_name = suiteName;
                }
                return static_cast<Suite *>(GLOBAL_suite.get());
            }

            static std::string GLOBAL_last_suite_name;
            static std::unique_ptr<ISuite> GLOBAL_suite;

            static OrderedTests GLOBAL_tests_ptr;
        };        

        template <typename Mock>
        std::string GeneralTests<Mock>::GLOBAL_last_suite_name = "";

        template <typename Mock>
        std::unique_ptr<ISuite> GeneralTests<Mock>::GLOBAL_suite = nullptr;

        template <typename Mock>
        OrderedTests GeneralTests<Mock>::GLOBAL_tests_ptr = OrderedTests();

} //namespace Cpp11_unit

#endif //TESTS_EXECUTOR_H_
