#ifndef GUN_TEST_TEST_KEEPER_H_
#define GUN_TEST_TEST_KEEPER_H_

#include <iostream>
#include <vector>
#include "Structures.h"

#define TS_GEN_ADD_TEST(testPtr) gun::test::TestsKeeper<gun::test::Mock>::addTest(testPtr)

// TODO maybe it's not a rigth way for all compilers!
#define TS_GEN_ENSURE_TEST_STORE_CREATED \
    TestsKeeper<Mock>::GLOBAL_added_tests_ptr.front()

namespace gun { namespace test {

        class ITest;

        // using AddedTests = std::vector<ITest *>;
        class AddedTests : public std::vector<ITest *>
        {
        public:
            AddedTests() {
                TRACE_PRINT("Create AddedTests obj");
            }
            ~AddedTests() = default;
        };

        template<typename Mock>
        class TestsKeeper {
        public:

            static void addTest(ITest *test) {
                TRACE_PRINT("Add test");
                if (test != nullptr) {
                    TRACE_PRINT("Not empty!");
                    GLOBAL_added_tests_ptr.emplace_back(test);
                    TRACE_VAR(GLOBAL_added_tests_ptr.size());
                }
            }

        protected:
            TestsKeeper() = default;
            friend ITest;
            static AddedTests GLOBAL_added_tests_ptr;
        };        

        template <typename Mock>
        AddedTests TestsKeeper<Mock>::GLOBAL_added_tests_ptr = AddedTests();

} } //namespace test and gun

#endif //GUN_TEST_TEST_KEEPER_H_
