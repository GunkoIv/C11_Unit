// Кодировка utf-8.
#ifndef TESTS_ASSERT_H_
#define TESTS_ASSERT_H_

#include <string>
#include "Structures.h"
#include <sstream>

// THANKS a lot for https://stackoverflow.com/questions/1597007/creating-c-macro-with-and-line-token-concatenation-with-positioning-macr
#define TOKENPASTE(x, y) x ## y
#define TOKENPASTE2(x, y) TOKENPASTE(x, y)
// TODO for many compilers can be used __COUNTER__ instead __LINE__ 
#define ASSERT(Expr) Cpp11_unit::AssertCheckHelper TOKENPASTE2(Assert, __LINE__) = \
    Cpp11_unit::TestResult(Expr, "ASSERT FAULT", #Expr, CODE_INFO)

namespace Cpp11_unit {

class TestResult {
public:

    static TestResult Good() {
        TestResult noError{};
        return noError;
    }

    explicit TestResult(bool result, c_char_ar desc, c_char_ar expr, CodeInfo codeInfo)
    {
        if (! result) {
            m_isBad = true;
            codeInfo.printTo(m_description);
            m_description << '\n' << CLPrint<CLColor::RED>(desc) << ": " 
                << CLPrint<CLColor::RED>(expr);
        }
    }

    explicit TestResult(TestResult&& result, c_char_ar desc, c_char_ar expr, CodeInfo codeInfo)
    {
        if (result.m_isBad) {
            m_isBad = true;
            codeInfo.printTo(m_description);
            m_description << '\n' << CLPrint<CLColor::RED>(desc) << ": " 
                << result.m_description.str();
        }
    }

    // ~TestResult() = default;

    TestResult && unite(TestResult&& other) {
        m_isBad = m_isBad || other.m_isBad;
        m_description << other.m_description.str();
        return std::move(*this);
    }

    bool isBad() const {
        return m_isBad;
    }

    std::stringstream takeDescription() {
        return std::move(m_description);
    }

    template <typename T>
    // typename std::enable_if<is_printable<T>::value, TestResult>::type
    TestResult && operator << (T&& val) {
        if (m_isBad) {
            if ( ! m_isAddedUserInfo) {
                m_description << "\nUser Info: \"";
                m_isAddedUserInfo = true;
            }
            m_description << std::forward<T>(val);
        }
        return std::move(*this);
    }

    TestResult(TestResult &&other)
        : m_description(std::move(other.m_description))
        , m_isBad(other.m_isBad)
    {
        if (other.m_isAddedUserInfo) {
            m_description << '\"';
            // m_description << "\"\n";
        }
    }
    
private:
    TestResult() = default;

    std::stringstream m_description{};
    bool m_isAddedUserInfo = false;
    bool m_isBad = false;
};

class AssertCheckHelper {
public:
    AssertCheckHelper(TestResult&& result) {
        if (result.isBad()) {
            throw std::move(result);
        }
    }
    // NOTE To avoid compiler(gcc) warnings like: 
    // "variable ‘Assert104’ set but not used" which occur when explore ASSERT macros
    ~AssertCheckHelper() {}   
};

} //namespace Cpp11_unit

#endif //TESTS_ASSERT_H_
