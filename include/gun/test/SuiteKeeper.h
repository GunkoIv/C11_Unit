#ifndef GUN_TEST_SUITE_KEEPER_H_
#define GUN_TEST_SUITE_KEEPER_H_

#include <iostream>
#include "ISuite.h"

#define TS_GEN_GET_SUITE(TheSuite, SuiteName) \
    gun::test::SuiteKeeper<gun::test::Mock>::getSuite<TheSuite>(SuiteName)

namespace gun { namespace test {

        class ITest;

        template<typename Mock>
        class SuiteKeeper {
        public:

            template<typename TheSuite>
            static TheSuite * getSuite(const std::string &suiteName) {
                // std::cout << "See to new suite" << std::endl;
                if (suiteName != GLOBAL_last_suite_name) {
                    std::cout << "teardown old and create new suite " << std::endl;
                    GLOBAL_suite.reset();
                    GLOBAL_suite.reset(new SetupWrapper<TheSuite>());
                    GLOBAL_last_suite_name = suiteName;
                }
                return static_cast<TheSuite *>(GLOBAL_suite.get());
            }
        protected:

            static std::string GLOBAL_last_suite_name;
            static std::unique_ptr<ISuite> GLOBAL_suite;
        };        

        template <typename Mock>
        std::string SuiteKeeper<Mock>::GLOBAL_last_suite_name = "";

        template <typename Mock>
        std::unique_ptr<ISuite> SuiteKeeper<Mock>::GLOBAL_suite = nullptr;

} } //namespace test and gun

#endif //GUN_TEST_SUITE_KEEPER_H_
