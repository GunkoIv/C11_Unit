#ifndef PROFILER_H_
#define PROFILER_H_

#include <iostream>
#include <string>
#include <cstring>
#include <type_traits>

#include <sstream>

namespace {

    template <typename T>
    struct has_iterator
    {
        template <typename U>
        static char test(typename U::iterator* x);
     
        template <typename U>
        static long test(U* x);
     
        static const bool value = sizeof(test<T>(0)) == 1;
    };

    template <typename T>
    struct is_map
    {
        template <typename U>
        static char test(typename U::mapped_type* x);
     
        template <typename U>
        static long test(U* x);
     
        static const bool value = sizeof(test<T>(0)) == 1;
    };

} // unname namespace

struct ToString {

    template<class ... Args> 
    ToString(Args&& ...args)
        : ss()
    {
        add(args...);
    }

    operator std::string() const {
        return ss.str();
    }

private:
    void add() {}

    template<class FirstArgument, class ... Args> 
    void add(const FirstArgument& first, Args& ...args) {
        addElem(first);
        add(args...);
    }

    void addElem(const std::string& str) {
        ss << str;
    }

    template <typename T>
    typename std::enable_if<!has_iterator<T>::value, void>::type addElem(const T& x) {
        ss << x;
    }

    template <typename T>
    typename std::enable_if<is_map<T>::value, void>::type addElem(const T& container) {
        ss << "MapContainer: ";
        for(const auto &elem : container) {
            ss << elem.first << ":" << elem.second << "; ";
        }
}
     
    template <typename T>
    typename std::enable_if<has_iterator<T>::value && !is_map<T>::value, void>::type addElem(const T& container) {
        ss << "Container: ";
        for(const auto &elem : container) {
            ss << elem << "; ";
        }
    }

    std::stringstream ss;
};

void realdprintf(const char *fullFileName, int lineInFile, const std::string &str);

#ifdef TRACING

#define PROF_CERR(...) realdprintf(__FILE__, __LINE__, ToString(__VA_ARGS__))
#define PROF_SEG_FAULT()  { int *pointer = NULL; *pointer = 42; }

#else // ifndef TRACING

#define PROF_CERR(...) {}
#define PROF_SEG_FAULT()  {}

#endif //TRACING

#endif //PROFILER_H_