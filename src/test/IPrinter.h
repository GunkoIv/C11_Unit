// Кодировка utf-8.
#ifndef TESTS_IPRINTER_H_
#define TESTS_IPRINTER_H_

#include "Structures.h"
#include "../cLPrint.h"

namespace Cpp11_unit {

        class IPrinter {
        public:

            template<typename ...Args>
            void print(Args&& ...args) {
                pass{(std::cout << args, 1)...};
                std::cerr << '\n';
            }

            template<typename ...Args>
            void formatPrint(const std::string &str, Args&& ...args) {
                std::cerr << CLPrint<CLColor::GREEN>("Some format printing ") << str;
                pass{(std::cout << args, 1)...};
                std::cerr << '\n';
            }
        };
        
} //namespace Cpp11_unit

#endif //TESTS_IPRINTER_H_
