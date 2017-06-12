// Кодировка utf-8.
#ifndef TESTS_EXECUTOR_H_
#define TESTS_EXECUTOR_H_

#include <iostream>
#include "ITest.h"
#include "ITestSuite.h"

// #define TS_GEN Cpp11_unit::GeneralTests<Cpp11_unit::Mock>

#define TESTS_START() Cpp11_unit::GeneralTests<Cpp11_unit::Mock>::run()

namespace Cpp11_unit {

        struct LessTestOrder {
            bool operator() (const ITest *const test1, const ITest *const test2) {
                if (test1->m_suiteInfo.order_num < test2->m_suiteInfo.order_num) {
                    return true;
                } else if (test1->m_suiteInfo.order_num > test2->m_suiteInfo.order_num) {
                    return false;
                }
                if (test1->m_suiteInfo.name < test2->m_suiteInfo.name) {
                    return true;
                } else if (test1->m_suiteInfo.name > test2->m_suiteInfo.name) {
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


        template<typename Mock>
        class GeneralTests 
            : public TestsKeeper<Mock> 
            , public SuiteKeeper<Mock> 
        { 
        public:
        
            using OrderedTests = std::set<ITest *, LessTestOrder>;

            static void run() {
                TRACE_VAR(TestsKeeper<Mock>::GLOBAL_added_tests_ptr.size());
                OrderedTests orderedTestsPtr{
                    std::begin(TestsKeeper<Mock>::GLOBAL_added_tests_ptr), 
                    std::end(TestsKeeper<Mock>::GLOBAL_added_tests_ptr)
                };
                std::cout << "orderedTestsPtr.size() = " << orderedTestsPtr.size() << std::endl;
                for(auto &test : orderedTestsPtr) {
                    do {
                        auto &&result = test->execute();
                        if (result.isBad()) {
                            std::cerr << result.takeDescription().str();
                        }
                    } while (test->switchGenerator());
                }
                if (SuiteKeeper<Mock>::GLOBAL_suite != nullptr) {
                    SuiteKeeper<Mock>::GLOBAL_suite.reset();
                }
            }
        
        };        

        // template <typename Mock>
        // AddedTests TestsKeeper<Mock>::GLOBAL_added_tests_ptr = AddedTests();
        
} //namespace Cpp11_unit

#endif //TESTS_EXECUTOR_H_
