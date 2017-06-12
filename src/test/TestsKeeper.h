// Кодировка utf-8.
#ifndef TESTS_TESTS_KEEPER_H_
#define TESTS_TESTS_KEEPER_H_

#include <iostream>
#include <vector>
#include "Structures.h"

#define TS_GEN_ADD_TEST(testPtr) Cpp11_unit::TestsKeeper<Cpp11_unit::Mock>::addTest(testPtr)

// TODO maybe it's not a rigth way for all compilers!
#define TS_GEN_ENSURE_TESTS_STORE_CREATED \
    TestsKeeper<Mock>::GLOBAL_added_tests_ptr.front()

namespace Cpp11_unit {

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

} //namespace Cpp11_unit

#endif //TESTS_TESTS_KEEPER_H_
