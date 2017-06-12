// Кодировка utf-8.
#ifndef TESTS_STRUCTURES_H_
#define TESTS_STRUCTURES_H_

#include <string>
#include <memory>
#include <list>
#include <deque>
#include <set>
#include "../profiler.h"

#define UNUSED_VAR(expr) { (void)(expr); } 

namespace Cpp11_unit {

        struct Mock {};

        template<typename T>
        using Container = std::deque<T>;
        
        using u_int = unsigned int;

        template<typename T>
        using OrderContainer = std::set<T>;

        template<typename T>
        using Unique = std::unique_ptr<T>;


        struct Default {
            static constexpr unsigned int defaultOrderNumber = 100;
        };


        struct SuiteInfo {
            SuiteInfo() = default;

            SuiteInfo(const std::string& name)
                : name(name)
            {}

            SuiteInfo(const std::string& name, unsigned int orderNumber)
                : name(name), order_num(orderNumber)
            {}

            const std::string name = "";
            const unsigned int order_num = Default::defaultOrderNumber + 1;
        };

        struct pass {
            template<typename ...Args>
            pass(Args&& ...args) {}
        };

        template<typename ClassToSetup>
        class SetupWrapper : public ClassToSetup {
        public:
            template<typename ...Args>
            SetupWrapper(Args&& ...args)
                : ClassToSetup(std::forward<Args>(args)...)
            {
                this->setup();
            }
            ~SetupWrapper(){
                this->teardown();
            }
        };

} //namespace Cpp11_unit

#endif //TESTS_STRUCTURES_H_
