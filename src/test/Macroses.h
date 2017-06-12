// Кодировка utf-8.
#ifndef TESTS_MACROSES_H_
#define TESTS_MACROSES_H_

#define TEST(ClassName) \
class ClassName : public Cpp11_unit::ITest { \
    void virtual execute_body() override; \
    ClassName(std::string &&name) \
       : ITest(std::move(name)) \
    { \
       registerTests(); \
    } \
    static ClassName m_self; \
    virtual ~ClassName() {} \
    ClassName(ClassName &&) = default; \
}; \
ClassName ClassName::m_self = ClassName(#ClassName); \
void ClassName::execute_body()

#define TEST_N(ClassName,OrderNumber) \
class ClassName : public Cpp11_unit::ITest { \
    void virtual execute_body() override; \
    ClassName(std::string &&name, unsigned int orderNumber) \
       : ITest(std::move(name), orderNumber) \
    { \
       registerTests(); \
    } \
    static ClassName m_self; \
    virtual ~ClassName() {} \
    ClassName(ClassName &&) = default; \
}; \
ClassName ClassName::m_self = ClassName(#ClassName, OrderNumber); \
void ClassName::execute_body()

#define TEST_S(ClassName,SuiteName) \
class ClassName : public Cpp11_unit::ITestSuite<SuiteName> { \
    void virtual execute_body() override; \
    ClassName(std::string &&name) \
       : ITestSuite<SuiteName>(std::move(name), \
        Cpp11_unit::SuiteInfo(SuiteName::getSuiteName(), SuiteName::getOrderNumber())) \
    { \
       registerTests(); \
    } \
    static ClassName m_self; \
    virtual ~ClassName() {} \
    ClassName(ClassName &&) = default; \
}; \
ClassName ClassName::m_self = ClassName(#ClassName); \
void ClassName::execute_body()

#define TEST_S_N(ClassName,SuiteName,OrderNumber) \
class ClassName : public Cpp11_unit::ITestSuite<SuiteName> { \
    void virtual execute_body() override; \
    ClassName(std::string &&name, unsigned int orderNumber) \
       : ITestSuite<SuiteName>(std::move(name), \
        Cpp11_unit::SuiteInfo(SuiteName::getSuiteName(), SuiteName::getOrderNumber()), orderNumber) \
    { \
       registerTests(); \
    } \
    static ClassName m_self; \
    virtual ~ClassName() {} \
    ClassName(ClassName &&) = default; \
}; \
ClassName ClassName::m_self = ClassName(#ClassName, OrderNumber); \
void ClassName::execute_body()

#define SUITE_N(SuiteName, SuiteOrderNumber) \
class SuiteName : public Cpp11_unit::ISuite { \
public: \
    static const std::string & getSuiteName() { \
        static std::string str = #SuiteName; \
        return str; \
    } \
    static unsigned int getOrderNumber() { \
        return SuiteOrderNumber; \
    } \
/*friend TS_GEN; */friend Cpp11_unit::SetupWrapper<SuiteName>; \
private:

#define SUITE(SuiteName) \
class SuiteName : public Cpp11_unit::ISuite { \
public: \
    static const std::string & getSuiteName() { \
        static std::string str = #SuiteName; \
        return str; \
    } \
    static unsigned int getOrderNumber() { \
        return Cpp11_unit::Default::defaultOrderNumber; \
    } \
/*friend TS_GEN; */friend Cpp11_unit::SetupWrapper<SuiteName>; \
private:

#define SUITE_END };

#endif //TESTS_MACROSES_H_
