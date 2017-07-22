#ifndef GUN_TEST_EXECUTOR_H_
#define GUN_TEST_EXECUTOR_H_

#include <iostream>
#include "ITest.h"
#include "ITestSuite.h"

#define TESTS_EXECUTE(settings) gun::test::GeneralTests<gun::test::Mock>::runTestsExecute(settings)

namespace gun { namespace test {

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

        class Settings {
        public:
            
        };

        template<typename Mock>
        class GeneralTests 
            : public TestsKeeper<Mock> 
            , public SuiteKeeper<Mock> 
        { 
        public:
        
            using OrderedTests = std::set<ITest *, LessTestOrder>;
            const static constexpr char *separator = 
"==============================================================================\n";
            const static constexpr char *separatorThin = 
"______________________________________________________________________________\n";

            static void printHellowInfo() {
                // TODO use some 'printer'; add more Info
                std::cout << separatorThin << 
                    CLPrint<CLColor::GREEN>("C11_Unit Lanched") << 
                    '\n' << separatorThin << std::flush
                ;
            }

            static int runTestsExecute(const Settings& /**/) {
                printHellowInfo();
                int returnValue = EXIT_SUCCESS;
                
                TRACE_VAR(TestsKeeper<Mock>::GLOBAL_added_tests_ptr.size());
                OrderedTests orderedTestsPtr{
                    std::begin(TestsKeeper<Mock>::GLOBAL_added_tests_ptr), 
                    std::end(TestsKeeper<Mock>::GLOBAL_added_tests_ptr)
                };
                // TODO use some 'printer'
                std::cout << "Number Collected Test = " << 
                    CLPrint<CLColor::YELLOW>(orderedTestsPtr.size()) << 
                    '\n' << separatorThin << std::endl;
                std::stringstream errorsMsg{};
                for(auto &test : orderedTestsPtr) {
                    auto testID = std::string("Test: ") + 
                        ((test->getSuiteName() == "") ? (std::string()) : (test->getSuiteName() + ":")) + 
                        test->getTestName()
                    ;
                    std::cout << testID << std::flush;
                    do {
                        auto &&result = test->execute();
                        if (result.isBad()) {
                            errorsMsg << separator << testID << "\n" <<
                                result.takeDescription().str() << 
                                '\n' << separator << std::flush
                            ;
                            std::cout << CLPrint<CLColor::RED>(" FAULT") << std::endl;
                            returnValue = EXIT_FAILURE;
                        } else {
                            std::cout << CLPrint<CLColor::GREEN>(" OK") << std::endl;
                        }
                    } while (test->switchGenerator());
                }
                if (SuiteKeeper<Mock>::GLOBAL_suite != nullptr) {
                    SuiteKeeper<Mock>::GLOBAL_suite.reset();
                }
                std::cerr << errorsMsg.str() << std::endl;
                return returnValue;
            }
        
        };        
        
} } //namespace test and gun

#endif //GUN_TEST_EXECUTOR_H_
