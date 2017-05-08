// Кодировка utf-8.
#ifndef TESTS_ISUITE_H_
#define TESTS_ISUITE_H_

#include "Structures.h"
#include "IPrinter.h"
#include "IFixture.h"

namespace Cpp11_unit {

        class LessTestOrder;
    
        class ISuite {
        friend LessTestOrder; 
        public:
            
            virtual ~ISuite() {}

            ISuite()
            {
            }

            template<typename ...Args>
            void print(Args&& ...args) {
                m_printer->print(std::forward<Args>(args)...);
            }

            template<typename ...Args>
            void formatPrint(const std::string &str, Args&& ...args) {
                m_printer->formatPrint(str, std::forward<Args>(args)...);
            }

            virtual void setup() {}
            virtual void teardown() {}
            
        private:

            Unique<IPrinter> m_printer;
            Container<IFixture> m_fixtures {};
        };

        struct SuiteInfo {
            SuiteInfo()
            {}
            SuiteInfo(const std::string& name)
                : m_name(name)
            {}
            SuiteInfo(const std::string& name, unsigned int orderNumber)
                : m_name(name), m_order_num(orderNumber)
            {}
            const std::string m_name = "";
            const unsigned int m_order_num = 0;
        };
        template<typename Suite = ISuite>
        using SuiteSPtr = std::shared_ptr<Suite>;

} //namespace Cpp11_unit

#endif //TESTS_ISUITE_H_
