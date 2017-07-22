#ifndef GUN_TEST_MACROSES_H_
#define GUN_TEST_MACROSES_H_

#define TEST(ClassName) \
class ClassName : public gun::test::ITest { \
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
class ClassName : public gun::test::ITest { \
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
class ClassName : public gun::test::ITestSuite<SuiteName> { \
    void virtual execute_body() override; \
    ClassName(std::string &&name) \
       : ITestSuite<SuiteName>(std::move(name), \
        gun::test::SuiteInfo(SuiteName::getSuiteName(), SuiteName::getOrderNumber())) \
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
class ClassName : public gun::test::ITestSuite<SuiteName> { \
    void virtual execute_body() override; \
    ClassName(std::string &&name, unsigned int orderNumber) \
       : ITestSuite<SuiteName>(std::move(name), \
        gun::test::SuiteInfo(SuiteName::getSuiteName(), SuiteName::getOrderNumber()), orderNumber) \
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
class SuiteName : public gun::test::ISuite { \
public: \
    static const std::string & getSuiteName() { \
        static std::string str = #SuiteName; \
        return str; \
    } \
    static unsigned int getOrderNumber() { \
        return SuiteOrderNumber; \
    } \
/*friend TS_GEN; */friend gun::test::SetupWrapper<SuiteName>; \
private:

#define SUITE(SuiteName) \
class SuiteName : public gun::test::ISuite { \
public: \
    static const std::string & getSuiteName() { \
        static std::string str = #SuiteName; \
        return str; \
    } \
    static unsigned int getOrderNumber() { \
        return gun::test::Default::defaultOrderNumber; \
    } \
/*friend TS_GEN; */friend gun::test::SetupWrapper<SuiteName>; \
private:

#define SUITE_END };

#endif //GUN_TEST_MACROSES_H_
