#ifndef GUN_TEST_IPRINTER_H_
#define GUN_TEST_IPRINTER_H_

#include "Structures.h"
#include "../utils/cLPrint.h"

namespace gun { namespace test {

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
        
} } //namespace test and gun

#endif //GUN_TEST_IPRINTER_H_
