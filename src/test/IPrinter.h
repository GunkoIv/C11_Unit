// Кодировка utf-8.
#ifndef TESTS_IPRINTER_H_
#define TESTS_IPRINTER_H_

#include "Structures.h"

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
                std::cerr << "\n\033[1;31mSome format printing:\033[0m " << str;
                // See https://en.wikipedia.org/wiki/ANSI_escape_code
                // http://stackoverflow.com/questions/2616906/how-do-i-output-coloured-text-to-a-linux-terminal
                pass{(std::cout << args, 1)...};
                std::cerr << '\n';
            }
        };
        
} //namespace Cpp11_unit

#endif //TESTS_IPRINTER_H_
