// Кодировка utf-8.
#include "executor.h"

// class UserTest1 : public Cpp11_unit::ITest {
// public:
//     bool virtual exucute();

// private:

//     UserTest1(std::string name)
//        : m_name(name)
//     {
//         TS_GEN::addTest(this);
//     }

//     UserTest1(UserTest1 &&other)
//        : m_name(std::move(other.m_name))
//     {
//         TS_GEN::addTest(this);
//     }

//     std::string m_name;
//     static UserTest1 myself;
// };

// UserTest1 UserTest1::myself = UserTest1("UserTest1");

// bool UserTest1::exucute() {
//     outputInfo("Test with name '" + m_name + "' Start execution!");
//     return true;
// }

class test2
{
public:
    test2() {
        std::cout << "static Var!!!"<< std::endl;
    }
    ~test2() {}
    static test2 statVar;   
};

test2 test2::statVar = test2();
