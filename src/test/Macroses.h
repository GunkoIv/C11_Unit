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
    virtual ~ClassName() {} \
    ClassName(ClassName &&) = default; \
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
    virtual ~ClassName() {} \
    ClassName(ClassName &&) = default; \
}; \
ClassName ClassName::m_self = ClassName(#ClassName, OrderNumber); \
bool ClassName::exucute()

#define TEST_SIMPLE_S(ClassName,SuiteName) \
class ClassName : public Cpp11_unit::ITest { \
public: \
    bool virtual execute_native(); \
    bool virtual exucute() { \
        suite = TS_GEN::getSuite<SuiteName>(getSuiteName());\
        return execute_native(); \
    } \
private: \
    SuiteName* suite; \
    ClassName(std::string &&name) \
       : ITest(std::move(name), Cpp11_unit::suite_info::SuiteName()) \
    { \
        TS_GEN::addTest(this); \
    } \
    static ClassName m_self; \
    virtual ~ClassName() {} \
    ClassName(ClassName &&) = default; \
}; \
ClassName ClassName::m_self = ClassName(#ClassName); \
bool ClassName::execute_native()

#define TEST_SIMPLE_S_N(ClassName,SuiteName,OrderNumber) \
class ClassName : public Cpp11_unit::ITest { \
public: \
    bool virtual execute_native(); \
    bool virtual exucute() { \
        suite = TS_GEN::getSuite<SuiteName>(getSuiteName());\
        return execute_native(); \
    } \
private: \
    SuiteName* suite; \
    ClassName(std::string &&name, unsigned int orderNumber) \
       : ITest(std::move(name), Cpp11_unit::suite_info::SuiteName(), orderNumber) \
    { \
        TS_GEN::addTest(this); \
    } \
    static ClassName m_self; \
    virtual ~ClassName() {} \
    ClassName(ClassName &&) = default; \
}; \
ClassName ClassName::m_self = ClassName(#ClassName, OrderNumber); \
bool ClassName::execute_native()

#define SUITE(SuiteName) \
namespace Cpp11_unit { namespace suite_info { \
    struct SuiteName : public SuiteInfo  { \
        SuiteName() : SuiteInfo(#SuiteName, Default::defaultOrderNumber) \
        {} \
    }; \
}} \
class SuiteName : public Cpp11_unit::ISuite { \
private: \
    const std::string & getSuiteName() { \
        static std::string str = #SuiteName; \
        return str; \
    } \
friend TS_GEN; friend Cpp11_unit::SetupWrapper<SuiteName>; 

#define SUITE_N(SuiteName, SuiteNumber) \
namespace Cpp11_unit { namespace suite_info { \
    struct SuiteName : public SuiteInfo  { \
        SuiteName() : SuiteInfo(#SuiteName, SuiteNumber) \
        {} \
    }; \
}} \
class SuiteName : public Cpp11_unit::ISuite { \
private: \
    const std::string & getSuiteName() { \
        static std::string str = #SuiteName; \
        return str; \
    } \
friend TS_GEN; friend Cpp11_unit::SetupWrapper<SuiteName>; 

#define SUITE_END };

#endif //TESTS_MACROSES_H_
