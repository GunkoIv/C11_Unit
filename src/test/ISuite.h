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

            ISuite(std::string &&name)
                : m_name(std::move(name))
            {}
            
        protected: 
            
            const std::string & getSuiteName() {
                return m_name;
            }

        private:
            const std::string m_name;

            Unique<IPrinter> m_printer;
            Container<IFixture> m_fixtures {};
        };

        using SuiteSPtr = std::unique_ptr<ISuite>;

} //namespace Cpp11_unit

#endif //TESTS_ISUITE_H_
