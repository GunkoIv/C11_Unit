// Кодировка utf-8.
#ifndef TO_STRING_H_
#define TO_STRING_H_

#include <iostream>
#include <string>
#include <cstring>
#include <type_traits>
#include <assert.h>

#include <sstream>

namespace {

    template <typename T>
    struct has_iterator
    {
        template <typename U>
        static char test(typename U::iterator* x);
     
        template <typename U>
        static long test(U* x);
     
        static const bool value = sizeof(test<typename std::remove_reference<T>::type>(0)) == 1;
    };

    template <typename T>
    struct is_map
    {
        template <typename U>
        static char test(typename U::mapped_type* x);
     
        template <typename U>
        static long test(U* x);
     
        static const bool value = sizeof(test<typename std::remove_reference<T>::type>(0)) == 1;
    };

} // unname namespace

struct ToString {

    ToString(ToString &&) = default;

    template<class ... Args> 
    ToString(Args&& ...args)
        : ss()
    {
        ss << std::boolalpha;
        add(std::forward<Args>(args)...);
    }

    operator std::string() const {
        return ss.str();
    }

    operator std::stringbuf*() const {
        return ss.rdbuf();
    }

private:
    void add() {}

    template<class FirstArgument, class ... Args> 
    void add(FirstArgument&& first, Args&& ...args) {
        addElem(std::forward<FirstArgument>(first));
        add(std::forward<Args>(args)...);
    }

    void addElem(std::string&& str) {
        ss << std::forward<std::string>(str);
    }

    template <typename T>
    typename std::enable_if<has_iterator<T>::value && !is_map<T>::value, void>::type 
    addElem(T&& container) {
        ss << "{";
        bool isFirst = true;
        for(auto &&elem : container) {
            (isFirst) ? (isFirst=false) : (ss << ", ", true);
            ss << "'" << elem << "'";
        }
        ss << "}";
    }

    template <typename T>
    typename std::enable_if<!has_iterator<T>::value, void>::type addElem(T&& x) {
        ss << std::forward<T>(x);
    }

    // template <typename T>
    // void addElem(T&& x) {
    //     static_assert(false, "unable to convert input object to string type");
    // }

    template <typename T>
    typename std::enable_if<is_map<T>::value, void>::type
    addElem(const T& map) {
        ss << "{";
        bool isFirst = true;
        for(const auto &elem : map) {
            (isFirst) ? (isFirst=false) : (ss << ", ", true);
            ss << "'" << elem.first << "'" << " : '" << elem.second << "'";
        }
        ss << "}";
    }

    std::stringstream ss;
};

#endif // TO_STRING_H_
