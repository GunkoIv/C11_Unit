#ifndef GUN_TEST_ISUITE_H_
#define GUN_TEST_ISUITE_H_

#include "Structures.h"
#include "IPrinter.h"
#include "IFixture.h"

namespace gun { namespace test {

        class LessTestOrder;
    
        class ISuite {
        friend LessTestOrder; 
        public:
            
            virtual ~ISuite() {}

            ISuite()
            {}

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

        template<typename Suite = ISuite>
        using SuiteSPtr = std::shared_ptr<Suite>;

} } //namespace test and gun

#endif //GUN_TEST_ISUITE_H_
