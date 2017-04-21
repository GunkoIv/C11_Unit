// Кодировка utf-8.
#ifndef TESTS_STRUCTURES_H_
#define TESTS_STRUCTURES_H_

#include <string>
#include <memory>
#include <list>
#include <deque>
#include <set>

namespace Cpp11_unit {

        template<typename T>
        using Container = std::deque<T>;

        template<typename T>
        using OrderContainer = std::set<T>;

        template<typename T>
        using Unique = std::unique_ptr<T>;

        struct Default {
            static constexpr unsigned int defaultOrderNumber = 100;
        };

        struct pass {
            template<typename ...Args>
            pass(Args&& ...args) {}
        };

} //namespace Cpp11_unit

#endif //TESTS_STRUCTURES_H_
