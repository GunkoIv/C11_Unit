// Кодировка utf-8.
// #include "executor.h"
#include <iostream>

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
