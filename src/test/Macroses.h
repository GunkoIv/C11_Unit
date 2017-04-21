// Кодировка utf-8.
#ifndef TESTS_MACROSES_H_
#define TESTS_MACROSES_H_

#define TEST_SIMPLE(ClassName) \
class ClassName : public Cpp11_unit::ITest { \
public: \
    bool virtual exucute(); \
private: \
    ClassName(std::string &&name) \
       : ITest(std::move(name)) \
    { \
        TS_GEN::addTest(this); \
    } \
    static ClassName m_self; \
}; \
ClassName ClassName::m_self = ClassName(#ClassName); \
bool ClassName::exucute()

#define TEST_SIMPLE_N(ClassName,OrderNumber) \
class ClassName : public Cpp11_unit::ITest { \
public: \
    bool virtual exucute(); \
private: \
    ClassName(std::string &&name, unsigned int orderNumber) \
       : ITest(std::move(name), orderNumber) \
    { \
        TS_GEN::addTest(this); \
    } \
    static ClassName m_self; \
}; \
ClassName ClassName::m_self = ClassName(#ClassName, OrderNumber); \
bool ClassName::exucute()

#define TEST_SIMPLE_S(ClassName,SuiteName) \
class ClassName : public Cpp11_unit::ITest { \
public: \
    bool virtual exucute(); \
private: \
    ClassName(std::string &&name, SuiteSPtr suiteSptr) \
       : ITest(std::move(name), suiteSptr) \
    { \
        TS_GEN::addTest(this); \
    } \
    static ClassName m_self; \
}; \
ClassName ClassName::m_self = ClassName(#ClassName, SuiteSPtr(new SuiteName(#SuiteName))); \
bool ClassName::exucute()

#endif //TESTS_MACROSES_H_
